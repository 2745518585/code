#pragma once
#ifndef _COMMAND_CHECK
#define _COMMAND_CHECK _COMMAND_CHECK
#include"orita.hpp"
class Command_check: public App
{
  protected:
    void defineOptions(Poco::Util::OptionSet &options)
    {
        options.addOption(Poco::Util::Option("help","h","display help information").noArgument());
        options.addOption(Poco::Util::Option("ifile","if","specify data maker").argument("file",true));
        options.addOption(Poco::Util::Option("ofile","of","specify std").argument("file",true));
        options.addOption(Poco::Util::Option("afile","af","specify ans").argument("file",true));
        options.addOption(Poco::Util::Option("checker","c","specify checker").argument("file",true));
        options.addOption(Poco::Util::Option("num","n","specify check num").argument("num",true));
        options.addOption(Poco::Util::Option("time","t","change time limit").argument("time",true));
        App::defineOptions(options);
    }
    void displayHelp(Poco::Util::HelpFormatter *helpFormatter)
    {
        helpFormatter->setHeader("Orita - Check");
        helpFormatter->setCommand("orita check");
        helpFormatter->setUsage("[options]\n");
        helpFormatter->setFooter(" ");
        helpFormatter->format(std::cout);
    }
    int main(const std::vector<std::string>& args)
    {
        loadConfiguration();
        if(check_option("error options")) return EXIT_USAGE;
        if(check_option("help")) return EXIT_OK;
        INFO("args",vec_to_str(args,static_cast<std::string(*)(const std::string&)>(add_squo)));


        const std::string _in_name="data_maker";
        const std::string _out_name="std";
        const std::string _ans_name="ans";
        const std::string _chk_name="checker";
        // init name
        fil in=[&]()
        {
            pat in_str=check_file(get_option("ifile"),_check_in);
            add_file(_check_in,in_str);
            return add_namesuf(get_file(in_str),"cpp");
        }();
        fil out=[&]()
        {
            pat out_str=check_file(get_option("ofile"),_check_out);
            add_file(_check_out,out_str);
            return add_namesuf(get_file(out_str),"cpp");
        }();
        fil ans=[&]()
        {
            pat ans_str=check_file(get_option("afile"),_check_ans);
            add_file(_check_ans,ans_str);
            return add_namesuf(get_file(ans_str),"cpp");
        }();
        fil chk=[&]()
        {
            pat chk_str=check_file(get_option("checker"),_check_chk);
            add_file(_check_chk,chk_str);
            return add_namesuf(get_file(chk_str),"cpp");
        }();
        // init time
        if(check_option("time")) change_time_limit((tim)std::stoi(get_option("time")));
        // init total sum
        if(!check_option("num"))
        {
            print_result(res::type::SS);
            return EXIT_OK;
        }
        unsigned total_sum=std::stoi(get_option("num"));
        // init data dir
        try
        {
            if(default_data_dir.exists()) default_data_dir.remove(true);
            default_data_dir.createDirectory();
            (default_data_dir/"datas").createDirectory();
            INFO("make data dir",add_squo(default_data_dir.path()));
        }
        catch(...)
        {
            ERROR("make data dir - fail",add_squo(default_data_dir.path()));
            throw Poco::Exception("fail make data dir");
        }
        // find file
        if(in==fil()||!in.exists()) {print_result(_in_name,res::type::NF);return EXIT_NOINPUT;}
        if(out==fil()||!out.exists()) {print_result(_out_name,res::type::NF);return EXIT_NOINPUT;}
        if(ans==fil()||!ans.exists()) {print_result(_ans_name,res::type::NF);return EXIT_NOINPUT;}
        if(chk==fil()||!chk.exists()) {print_result(_chk_name,res::type::NF);return EXIT_NOINPUT;}
        scout<<termcolor::bright_grey<<print_type({std::string(" ")*60,"","\n"},{{_in_name+": ",in.path()},{_out_name+": ",out.path()},{_ans_name+": ",ans.path()},{_chk_name+": ",chk.path()}})<<ANSI::move_up*4<<termcolor::reset;
        // compile file
        printer loading_printer({"Compiling.","Compiling..","Compiling..."},(tim)150);
        loading_printer.start();
        compiler *run_compiler=new compiler(4);
        run_compiler->add({{_in_name,in},{_out_name,out},{_ans_name,ans},{_chk_name,chk}},data_compile_argu);
        run_compiler->wait({_in_name,_out_name,_ans_name,_chk_name});
        {
            auto compile_result=run_compiler->get({_in_name,_out_name,_ans_name,_chk_name});
            if(compile_result.first)
            {
                loading_printer.stop();
                print_result(compile_result.second,res::type::CE);
                return EXIT_OK;
            }
        }
        delete run_compiler;
        loading_printer.stop();
        // check
        unsigned ac_sum=0,runned_sum=0;
        for(int i=1;i<=total_sum;++i)
        {
            scout<<std::string("-")*50<<"\r#"<<i;
            if(runned_sum!=ac_sum)
            {
                scout<<std::string("-")*(30-std::to_string(i).size())<<termcolor::bright_grey<<" Unaccepted "<<termcolor::bright_red<<runned_sum-ac_sum<<" "<<termcolor::reset;
            }
            scout<<"\n";
            fil run_dir=default_data_dir/"datas"/std::to_string(i);
            run_dir.createDirectory();
            fil in_file=run_dir/"data.in",out_file=run_dir/"data.out",ans_file=run_dir/"data.ans",chk_file=run_dir/"data.txt";
            unsigned seed=rnd();
            runner in_runner(in,system_nul,in_file,std::to_string(seed));
            if(in_runner.run()) {print_result(_in_name,res::type::TO,in_runner.time);continue;}
            if(in_runner.exit_code) {print_result(_in_name,res::type::RE,(tim)0,in_runner.exit_code);continue;}
            runner out_runner(out,in_file,out_file);
            if(out_runner.run()) {print_result(_out_name,res::type::TO,out_runner.time);continue;}
            if(out_runner.exit_code) {print_result(_out_name,res::type::RE,(tim)0,out_runner.exit_code);continue;}
            judger ans_judger(ans,chk,in_file,out_file,ans_file,chk_file);
            ans_judger.judge();
            ans_judger.print_result();
            sofstream output_chk_file(chk_file,std::ios::app);
            output_chk_file<<"\n"<<std::string("*")*50<<"\n";
            output_chk_file<<"    result: "<<get_resultname(ans_judger.result)<<"\n";
            output_chk_file<<"    seed: "<<seed<<"\n";
            output_chk_file<<print_type({"    ",": time: "," exit_code: ","\n"},{{_in_name,in_runner.time,in_runner.exit_code},{_out_name,out_runner.time,out_runner.exit_code},{_ans_name,ans_judger.time,ans_judger.exit_code},{_chk_name,ans_judger.chk_time,ans_judger.chk_exit_code}});
            output_chk_file<<std::string("*")*50;
            output_chk_file.close();
            if(!ans_judger.result.isnull()) ++runned_sum;
            if(ans_judger.result.istrue()) ++ac_sum;
            if(ans_judger.result.isfalse())
            {
                run_dir.copyTo((default_data_dir/(std::to_string(i)+" - "+get_short_resultname(ans_judger.result))).path());
            }
        }
        scout<<"\n"<<ac_sum<<" / "<<runned_sum<<"\n\n";
        return EXIT_OK;
    }
};
#endif