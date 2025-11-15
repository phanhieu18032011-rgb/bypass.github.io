// DRGcore – HieuDRG – Shadow License v99
const $ = id => document.getElementById(id);

const shortDomains = [
  'link4m.com','link2m.com','yeumonney.com','nhapcode1s.com',
  'link4sub.com','linkvertise.com','linkvertise.net'
];

const robloxKeys = [
  'krnl','delta','fluxus','synapse','scriptware'
];

function detectType(input){
  const u = new URL(input.startsWith('http')? input : 'https://'+input);
  if(shortDomains.some(d => u.hostname.includes(d))) return 'short';
  if(robloxKeys.some(k => input.toLowerCase().includes(k))) return 'key';
  return 'unknown';
}

async function bypassShort(url){
  // thử fetch qua cors-anywhere fallback
  const cors = 'https://api.allorigins.win/get?url=';
  const res = await fetch(cors+encodeURIComponent(url));
  const text = await res.text();
  // regex tìm href đích
  const m = text.match(/href=["'](https?:\/\/[^"']+)["']/);
  return m ? m[1] : 'Không tìm thấy link đích';
}

function bypassKey(key){
  // fake bypass demo – thực tế cần patch binary / memory
  return `Bypassed key "${key}" -> injected=true (client-side demo only)`;
}

async function bypass(){
  const val = $('url').value.trim();
  if(!val) return $('out').textContent = 'Nhập gì đó đi!';
  const type = detectType(val);
  let result;
  if(type==='short') result = await bypassShort(val);
  else if(type==='key') result = bypassKey(val);
  else result = 'Không hỗ trợ loại này';
  $('out').textContent = result;
}
