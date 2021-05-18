with Libadalang.Analysis;
with Libadalang.Common;

package Lal_Adapter.Node is
   package LAL renames Libadalang.Analysis;
   package LALCO renames Libadalang.Common;

   type Class (Trace : Boolean := False) is tagged limited private; -- Initialized

   -- Process a node and all of its components:
   -- Raises Internal_Error for unhandled internal exceptions.
   procedure Process
     (This    : in out Class;
      Node    : in     LAL.Ada_Node'Class;
      --  Options : in     Options_Record;
      Outputs : in     Output_Accesses_Record);

private

   -- For debuggng:
   Parent_Name : constant String := Module_Name;
   Module_Name : constant String := Parent_Name & ".Node";

   type Class (Trace : Boolean := False) is tagged limited -- Initialized
      record
         -- Current, in-progress intermediate output products:
         -- Used when making dot edges to child nodes:
         Dot_Node  : Dot.Node_Stmt.Class; -- Initialized
         Dot_Label : Dot.HTML_Like_Labels.Class; -- Initialized
         A_Element  : a_nodes_h.Element_Struct := anhS.Default_Element_Struct;
         -- I would like to just pass Outputs through and not store it in the
         -- object, since it is all pointers and we don't need to store their
         -- values between calls to Traverse. Outputs has to go into
         -- Add_To_Dot_Label, though, so we'll put it in the object and pass
         -- the object to Add_To_Dot_Label:
         Outputs   : Output_Accesses_Record; -- Initialized
      end record;

   -- Helper methods for use by children:

   -- String
   procedure Add_To_Dot_Label
     (This  : in out Class;
      Name  : in     String;
      Value : in     String);

   -- Wide_String
   -- Add <Name> => <Value> to the label, and print it if trace is on:
   procedure Add_To_Dot_Label
     (This  : in out Class;
      Name  : in     String;
      Value : in     Wide_String);

   -- Element_ID
   -- Add <Name> => <Value> to the label, and print it if trace is on:
   procedure Add_To_Dot_Label
     (This  : in out Class;
      Name  : in     String;
      Value : in     a_nodes_h.Element_ID);

   -- Boolean
   -- Add <Name> => <Value> to the label, and print it if trace is on:
   procedure Add_To_Dot_Label
     (This  : in out Class;
      Name  : in     String;
      Value : in     Boolean);

   -- String:
   -- Add <Value> to the label, and print it if trace is on:
   procedure Add_To_Dot_Label
     (This  : in out Class;
      Value : in     String);

   type Ada_Versions is
     (Ada_83,
      Ada_95,
      Ada_2005,
      Ada_2012,
      Ada_2020);
   pragma Ordered (Ada_Versions);

   Supported_Ada_Version : constant Ada_Versions := Ada_95;

   -- If Ada_Version <= Supported_Ada_Version then:
   --    Add to dot label: ASIS_PROCESSING =>
   --      "NOT_IMPLEMENTED_COMPLETELY"
   --    and increment the Not_Implemented count
   -- Otherwise:
   --    Add to dot label: ASIS_PROCESSING =>
   --      Ada_Version & "_FEATURE_NOT_IMPLEMENTED_IN_" & Supported_Ada_Version
   procedure Add_Not_Implemented
     (This        : in out Class;
      Ada_Version : in     Ada_Versions := Supported_Ada_Version);

   procedure Add_Dot_Edge
     (This  : in out Class;
      From  : in     a_nodes_h.Element_ID;
      To    : in     a_nodes_h.Element_ID;
      Label : in     String);

   -- Add an edge and a dot label:
   procedure Add_To_Dot_Label_And_Edge
     (This  : in out Class;
      Label : in     String;
      To    : in     a_nodes_h.Element_ID);

   function To_Element_ID_List
     (This           : in out Class;
      Elements_In    : in     Asis.Element_List;
      Dot_Label_Name : in     String;
      Add_Edges      : in     Boolean := False)
      return  a_nodes_h.Element_ID_List;

   procedure Add_Element_List
     (This           : in out Class;
      Elements_In    : in     Asis.Element_List;
      Dot_Label_Name : in     String;
      List_Out       :    out a_nodes_h.Element_ID_List;
      Add_Edges      : in     Boolean := False);

end Lal_Adapter.Node;
