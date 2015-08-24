# List Of Api For js-psp #

/  /

JSBool js\_print(JSContext **cx, JSObject**obj, uintN argc, jsval **argv, jsval**rval);

/ /

JSBool js\_include(JSContext **cx, JSObject**obj, uintN argc, jsval **argv, jsval**rval);


/
- Make JS Function From C Function
- @param fun\_name - Function name
- /

JS\_FUN(fun\_name);

/
- Convert JS Value To int
- @param j - JS Value
- /

J2I(j);

/
- Convert JS Value To String
- @param j - JS Value
- /

J2S(j);

/
- Convert JS Value To u32 (unsigned int)
- @param j - JS Value
- /

J2U(j);

/
- Convert JS Value To Object (struct or other)
- @param j - JS Value
- /

J2O(j);

/
- Convert JS Value To long
- @param j - JS Value
- /

J2L(j);

/
- Convert int To JS Value
- @param j - JS Value
- /

I2J(i);

/
- Convert Object (struct or other) To JS Value
- @param j - JS Value
- /

O2J(i);