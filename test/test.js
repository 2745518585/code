const input = `
<span style="text-align: right; width: max-content; margin-left: 5px;"><span class="lv lv1" style="display: none;">2.5%</span><span class="lv lv2" style="display: none;">5.0%</span><span class="lv lv3" style="display: none;">7.5%</span><span class="lv lv4" style="display: none;">10.0%</span><span class="lv lv5" style="display: none;">12.5%</span><span class="lv lv6" style="display: none;">15.0%</span><span class="lv lv7" style="display: none;">17.5%</span><span class="lv lv8" style="display: none;">20.0%</span><span class="lv lv9" style="display: none;">22.5%</span><span class="lv lv10" style="">25.0%</span><span class="lv lv11" style="display: none;">28.0%</span><span class="lv lv12" style="display: none;">31.0%</span><span class="lv lv13" style="display: none;">34.0%</span><span class="lv lv14" style="display: none;">37.0%</span><span class="lv lv15" style="display: none;">40.0%</span></span>`
const regex = /style="(display: none;)?">(.*?)\%<\/span>/g;
const regex2 = /style="(display: none;)?">(.*?)\%\/(.*?)\%<\/span>/g;

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