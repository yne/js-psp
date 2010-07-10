printf("JavaScript-C 1.8.0 pre-release 1 2009-02-16\n");
var toto = include("prx/template.prx");
var kern = include("prx/template_driver.prx");
toto.template("hello");
printf(TEMPLATE_IS_LOADED+" \n");
