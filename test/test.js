const input = `
<span style="text-align: right; width: max-content; margin-left: 5px;"><span class="lv lv1" style="display: none;">336.96%+673.92%</span><span class="lv lv2" style="display: none;">362.232%+724.464%</span><span class="lv lv3" style="display: none;">387.504%+775.008%</span><span class="lv lv4" style="display: none;">421.2%+842.4%</span><span class="lv lv5" style="display: none;">446.472%+892.944%</span><span class="lv lv6" style="display: none;">471.744%+943.488%</span><span class="lv lv7" style="display: none;">505.44%+1010.88%</span><span class="lv lv8" style="display: none;">539.136%+1078.272%</span><span class="lv lv9" style="display: none;">572.832%+1145.664%</span><span class="lv lv10" style="">606.528%+1213.056%</span><span class="lv lv11" style="display: none;">640.224%+1280.448%</span><span class="lv lv12" style="display: none;">673.92%+1347.84%</span><span class="lv lv13" style="display: none;">716.04%+1432.08%</span><span class="lv lv14" style="display: none;">758.16%+1516.32%</span><span class="lv lv15" style="display: none;">800.28%+1600.56%</span></span>
`


const regex = /style="(display: none;)?">(.*?)\%<\/span>/g;
const regex2 = /style="(display: none;)?">(.*?)\%\+(.*?)\%<\/span>/g;

let match;
const results = [], resolts = [];

while ((match = regex2.exec(input)) !== null) {
  results.push(parseFloat((parseFloat(match[2].trim()) * 0.01).toPrecision(15)));
  resolts.push(parseFloat((parseFloat(match[3].trim()) * 0.01).toPrecision(15)));
}

if (resolts.length == 0) while ((match = regex.exec(input)) !== null) {
  results.push(parseFloat((parseFloat(match[2].trim()) * 0.01).toPrecision(15)));
}

console.log(`[${results.join(', ')}]`);
console.log(`[${resolts.join(', ')}]`);