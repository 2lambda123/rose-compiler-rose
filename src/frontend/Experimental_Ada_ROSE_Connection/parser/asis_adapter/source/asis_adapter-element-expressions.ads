package Asis_Adapter.Element.Expressions is

   procedure Do_Pre_Child_Processing
     (Element : in     Asis.Element;
      State   : in out Class);

private

   -- For debuggng:
   Parent_Name : constant String := Module_Name;
   Module_Name : constant String := Parent_Name & "Expressions";

end Asis_Adapter.Element.Expressions;
