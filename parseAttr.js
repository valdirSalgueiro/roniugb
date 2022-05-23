const fs = require("fs");

// var buf = fs.readFileSync("level1.png.map");
// word = [];
// for (i = 0; i < buf.length; i += 2)
//   word = [...word, "0x" + buf.readUInt8(i).toString(16).padStart(2, "0")];

var buf = fs.readFileSync("level1.map");
word = [];
for (i = 0; i < buf.length; i+=2)
  word = [...word, "0x" + buf.readUInt8(i+1).toString(16).padStart(2, "0")];

var text = "";
for (i = 0; i < word.length; i++)
{
  text+=word[i]+",";
}
console.log(text);