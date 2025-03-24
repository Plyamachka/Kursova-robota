function findRGBA(text) {
    const regex = /rgba\(\s*(\d{1,3})\s*,\s*(\d{1,3})\s*,\s*(\d{1,3})\s*,\s*(0|1|0?\.\d+)\s*\)/;
    const match = text.match(regex);
    if (match) {
    return match[0];
    } 
    else {
    return null;
}

}

console.log(findRGBA("This is a color rgba(255, 99, 71, 0.5) in text.")); 
console.log(findRGBA("No color here."));

function isIPAddress(ip) {
    const regex = /^(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])(\.(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])){3}$/;
    return regex.test(ip);
}

console.log(isIPAddress("192.168.1.1"));

function findRGBA(text) {
    const regex = /rgba\(\s*(\d{1,3})\s*,\s*(\d{1,3})\s*,\s*(\d{1,3})\s*,\s*(0|0?\.\d+|1)\s*\)/;
    const match = text.match(regex);
    return match ? match[0] : null;
}

console.log(findRGBA("Колір фону: rgba(255, 99, 71, 0.5);")); 
console.log(findRGBA("background: rgba(0,0,0,1); color: white;")); 
console.log(findRGBA("Це просто текст без кольору.")); 

function findHexColor(text) {
    const regex = /#([a-fA-F0-9]{3}|[a-fA-F0-9]{6})\b/;
    const match = text.match(regex);
    return match ? match[0] : null;
}

function findTags(text, tag) {
    const regex = new RegExp(`<${tag}\\b[^>]*>`, 'gi');
    return text.match(regex) || [];
}

function findPosNum(text) {
    const regex = /\b\d+(\.\d+)?\b/g;
    return (text.match(regex) || []).map(Number).filter(num => num > 0);
}

function findDates(text) {
    const regex = /\b\d{4}-\d{2}-\d{2}\b/g;
    return text.match(regex) || [];
}

function findEmail(text) {
    const regex = /\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}\b/g;
    return text.match(regex) || [];
}

console.log(findHexColor("Колір фону: #ff5733;"));
console.log(findHexColor("border: 1px solid #ABC;")); 

let s = '<div><img src="pic.jpg"><img src="logo.png"></div>';
console.log(findTags(s, "img"));

console.log(findPosNum("Температура: -5, 20.5 і 30 градусів.")); 

console.log(findDates("Події: 2023-05-12, 1999-12-31, 2024-02-29."));

console.log(findEmail("Контакти: user@example.com, test.mail@domain.net."));

