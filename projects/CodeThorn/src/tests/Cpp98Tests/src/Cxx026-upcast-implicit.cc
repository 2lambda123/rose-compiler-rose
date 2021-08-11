#include "test-new.h"
#include "test-main.h"

const char* description = "Tests subobject access using casts";
const char* expectedout = "{A1CA1BDfacfab~D~B~A~C~A}";

struct A
{
  explicit
  A(const char* val) : data(val) { printf("A1"); }

  A() : data("a")                { printf("A0"); }

  ~A() { printf("~A"); }

  const char* data;
};

struct B : A
{
  B() : A("ab"), data("b") { printf("B"); }
  ~B() { printf("~B"); }

  const char* data;
};

struct C : A
{
  C() : A("ac"), data("c") { printf("C"); }
  ~C() { printf("~C"); }

  const char* data;
};

struct D : C, B
{
  D() : C(), B(), data("d") { printf("D"); }
  ~D() { printf("~D"); }

  const char* data;
};

void f(const A& obj) { printf("f%s", obj.data); }

void run()
{
  D d;
  C& c = d;
  B& b = d;

  f(c);
  f(b);
}

