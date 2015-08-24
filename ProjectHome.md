`Open Source JavaScript interpreter based on SpiderMonkey 1.8 source`

## how does it work : ##
### by manually load the lib : ###
```
//load the Graphic Utility plugin
var gu = new Module("prx/gu.prx");

//use it methodes
gu.init(); //java(script) style
//or
sceGuInit();//c style
```
### using the auto plugin load feature : ###
```
sceGuInit(); //will load the "prx/gu.prx" plugin and then, call the function
```

### call lib's fonction and variables : ###
```
//local function
gu.init();
//global function
sceGuInit();
//local variable
gu.value;
//global variable
GU_TRUE
```

---
