#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#include "ROSETTA_macros.h"

#include <string>
#include "FileUtility.h"

class Grammar;
class GrammarString;
class AstNodeClass;

class SubclassListBuilder {
  std::vector<AstNodeClass*> children;

  public:
  SubclassListBuilder() {}
  // Yes, this is a mutating operation; the symbol was used for that before and
  // so we need to keep it
  SubclassListBuilder& operator|(const AstNodeClass& t);
  const std::vector<AstNodeClass*>& getList() const;
};

class AstNodeClass
{
  // Later we will template this class to permit it to refer to an arbitrary lower level grammar

  // Terminals for the basis for the definition of a grammar that defines a language
  // This class represents a AstNodeClass (the NonTerminal class is derived from the AstNodeClass class)

 public:
  // MS: 2013
  bool isInnerNode();
  bool isLeafNode();

  std::string   name;    // The name we assign to the token (e.g. "BinaryOperatorEquals")

  // where the name of the AstNodeClass is saved unmodified (with no grammar suffix)
  std::string baseName;

  // AstNodeClass/nonterminal for the base class of this AstNodeClass (set in the
  // NonTerminal constructor)
  AstNodeClass* baseClass;
                   
  // Subclasses of this AST node type
  std::vector<AstNodeClass *>    subclasses;

  // Can there be objects of this type (as opposed to just subclasses)?
  bool canHaveInstances;

  // The lexeme is used to build up the character string as the different operators 
  // are evaluated.  The when the operator| is called the lexeme is placed into the 
  // name (effectively naming the nonterminal).
  std::string   lexeme;  // The actual character string (e.g. "operator=")

  // Tag used within enum declaration (to that each AstNodeClass can be assigned an ID
  std::string   tag;

  // Relationship in lower level grammar (value == NULL only if a part of the C++ grammar)
  // This needs to be recorded into the classes that are build as well (I think)
  // We want to automatically set these (not sure if we can!)
  AstNodeClass* lowerLevelGramaticalElement;

  bool buildDefaultConstructor;

  // When a class is declared to implement the AstNodeClass object we must 
  // provide a mechanism for the declaration of class forwards (pre-declaration) 
  // and global variables (post-delaration) associated with the declaration 
  // of the class representing this AstNodeClass (it's object).
  std::string predeclarationString;
  std::string postdeclarationString;

  // Controls automatic generation of Constructors (using
  // declared data as input parameters) and Descructors
  bool automaticGenerationOfDestructor;
  bool automaticGenerationOfConstructor;
  bool automaticGenerationOfDataAccessFunctions;
  bool automaticGenerationOfCopyFunction;

  // Record the grammar that this AstNodeClass is associated with!
  Grammar* associatedGrammar;

  // Header file class definition function prototypes (local and subtree definitions)
  // Use an array of lists since every string has a local node/subtree 
  // representation and a local node/subtree exclude list
  std::vector<GrammarString *> memberFunctionPrototypeList[2][2];

  // Header file class definition data declarations (local and subtree definitions)
  std::vector<GrammarString *> memberDataPrototypeList[2][2];

  // Source code string lists (local and subtree definitions)
  std::vector<GrammarString *> memberFunctionSourceList[2][2];

  // String representation of '#if' that surrounds the class. If empty, then emits "#if 1"
  std::string cppCondition;

  // Wher class supports boost::serialization
  bool p_isBoostSerializable;

  enum locationInTree
  {
    LOCAL_LIST   = 0,
    SUBTREE_LIST = 1
  };

  enum includeExcludeMechanism
  {
    INCLUDE_LIST = 0,
    EXCLUDE_LIST = 1
  };

  // Access function for list objects
  std::vector<GrammarString *> & getMemberFunctionPrototypeList ( int i, int j ) const;
  std::vector<GrammarString *> & getMemberDataPrototypeList( int i, int j ) const;
  std::vector<GrammarString *> & getMemberFunctionSourceList( int i, int j ) const;

  // Mechanisms for adding elements to the lists (provides error checking)
  // testing work around for Insure++ (removing const to avoid copy generated by copy constructor)
#if !ROSE_MICROSOFT_OS
#if INSURE_BUG
  static void addElementToList ( std::vector<GrammarString *> & list,
                                 GrammarString & element );
#else
  static void addElementToList ( std::vector<GrammarString *> & list,
                                 const GrammarString & element );
#endif
#else
  static void addElementToList ( std::vector<GrammarString *> & list,
                                 const GrammarString & element );
#endif
  
  // Member function for checking lists of GrammarStrings occuring during the
  // class generation phase
  void checkListOfGrammarStrings(std::vector<GrammarString *>& list);

  // Storage of editing strings used for substitution of final output strings
  std::vector<GrammarString *> editSubstituteTargetList[2][2];
  std::vector<GrammarString *> editSubstituteSourceList[2][2];

  std::vector<GrammarString *> & getEditSubstituteTargetList( int i, int j ) const;
  std::vector<GrammarString *> & getEditSubstituteSourceList( int i, int j ) const;

  // Setup functions and data within the implementation
  // of the grammar represented by this nonTerminal
  void setFunctionPrototype        ( const GrammarString & memberFunction );
  void setFunctionPrototype        ( const std::string& markerString, const std::string& filename, 
                                     bool pureVirtual = false );

  void setSubTreeFunctionPrototype ( const GrammarString & memberFunction );
  void setSubTreeFunctionPrototype ( const std::string& markerString, const std::string& filename,
                                     bool pureVirtual = false );

  void setFunctionSource           ( const std::string& markerString, const std::string& filename, 
                                     bool pureVirtual = false );
  void setSubTreeFunctionSource    ( const std::string& markerString, const std::string& filename, 
                                     bool pureVirtual = false );

  // Mechanism for excluding code from specific node or subtrees
  void excludeFunctionPrototype        ( const GrammarString & memberFunction );
  void excludeFunctionPrototype        ( const std::string& markerString, const std::string& filename, 
                                         bool pureVirtual = false );
  void excludeSubTreeFunctionPrototype ( const GrammarString & memberFunction );
  void excludeSubTreeFunctionPrototype ( const std::string& markerString, const std::string& filename, 
                                         bool pureVirtual = false );

  void excludeFunctionSource           ( const std::string& markerString, const std::string& filename,
                                         bool pureVirtual = false );
  void excludeSubTreeFunctionSource    ( const std::string& markerString, const std::string& filename, 
                                         bool pureVirtual = false );

  void excludeSubTreeDataPrototype ( const GrammarString & inputMemberData );
  void excludeSubTreeDataPrototype ( const std::string& inputTypeNameString,
                                     const std::string& inputVariableNameString,
                                     const std::string& defaultInitializer );


  // Data is handled slightly differently, there are no subtree mechanisms
  // for handling data because data in base classes is by definition included
  // within derived classes.
  void setDataPrototype            ( const GrammarString & memberData); 

// AJ (12/3/2004): Added support for deleation of data members
  void setDataPrototype            ( const std::string& inputTypeNameString, 
                                     const std::string& inputVariableNameString, 
                                     const std::string& defaultInitializer,
                                     const ConstructParamEnum& constructorParameter,
                                     const BuildAccessEnum& buildAccessFunctions,
                                     const TraversalEnum& toBeTraversedDuringTreeTraversal,
                                     const DeleteEnum& delete_flag,
                                     const CopyConfigEnum& toBeCopied = COPY_DATA);

  virtual ~AstNodeClass ();

 protected:
  AstNodeClass ();
  GrammarString* setupMarkerStrings(std::string markerString, std::string fileName, bool pureVirtual);
 public:
  AstNodeClass ( const std::string& lexeme, Grammar & X, const std::string& stringVar, const std::string& tagString, bool canHaveInstances = true, const SubclassListBuilder & childList = SubclassListBuilder() );

  // Access functions
  void setConnectionToLowerLevelGrammar ( AstNodeClass & X );
  AstNodeClass & getConnectionToLowerLevelGrammar ();

  void  setLexeme ( const std::string& label = "defaultLexeme" );
  const std::string& getLexeme () const;
  void  setName   ( const std::string& label = "defaultName", const std::string& tagName = "" );
  const std::string& getName () const;
  void  setTagName   ( const std::string& label = "defaultTagName"   );
  const std::string& getTagName () const;
  const std::string& getBaseName () const;

  void setGrammar ( Grammar* grammarPointer );
  Grammar* getGrammar () const;

  void setBaseClass ( AstNodeClass* baseClassPointer );
  AstNodeClass* getBaseClass () const;

  bool isDerivedFrom(const std::string & s) const;

  void setCanHaveInstances (bool canHaveInstances);
  bool getCanHaveInstances() const;

  void addGrammarPrefixToName();

  void    setBuildDefaultConstructor ( bool X );
  bool    getBuildDefaultConstructor () const;

  std::string   buildDataAccessFunctions ( const GrammarString & inputMemberData);

  std::string buildConstructorBody( bool withInitializers, ConstructParamEnum config );

  // builds a constructor body for passing all data members as parameters
  std::string buildConstructorBodyForEssentialDataMembers();

  // AJ ( 10/26/2004)
  // Builds the destructor body
  std::string buildDestructorBody();

  void displayName ( int indent = 0 ) const;

                 // this stores the old and new string used for the substitution and applies
                 // it before final copying out of a node of the grammar to a file!
  void editSubstitute               ( const std::string& oldString, const std::string& newString );
  void editSubstituteSubTree        ( const std::string& oldString, const std::string& newString );
  void editSubstituteExclude        ( const std::string& oldString, const std::string& newString );
  void editSubstituteExcludeSubTree ( const std::string& oldString, const std::string& newString );

  void editSubstitute               ( const std::string& oldString, const std::string& markerName, const std::string& filename );
  void editSubstituteSubTree        ( const std::string& oldString, const std::string& markerName, const std::string& filename );
  void editSubstituteExclude        ( const std::string& oldString, const std::string& markerName, const std::string& filename );
  void editSubstituteExcludeSubTree ( const std::string& oldString, const std::string& markerName, const std::string& filename );

                 // Access functions for pre and post declaration strings
  void setPredeclarationString  ( const std::string& declarationString );
  void setPostdeclarationString ( const std::string& declarationString );
  void setPredeclarationString  ( const std::string& markerString, const std::string& filename );
  void setPostdeclarationString ( const std::string& markerString, const std::string& filename );

  const std::string& getPredeclarationString () const;
  const std::string& getPostdeclarationString() const;

                 // Sometimes we don't want the constructor to be automatically generated 
                 // because it must be specialied in a way that is not possible for the 
                 // automated tool (such cases represent asymetries in the design and so 
                 // they should be avoided).  In general such details should be handled 
                 // within the post_construction_initialization() member function.
  void setAutomaticGenerationOfConstructor         ( bool X = true );
  void setAutomaticGenerationOfDestructor          ( bool X = true );
  void setAutomaticGenerationOfDataAccessFunctions ( bool X = true );
  void setAutomaticGenerationOfCopyFunction        ( bool X = true );

                 // Access function for automaticGenerationOfDestructor and automaticGenerationOfConstructor
  bool generateDestructor () const;
  bool generateConstructor() const;
  bool generateDataAccessFunctions() const;
  bool generateCopyFunction() const;

// char* buildCopyMemberFunctionSource ();
  Rose::StringUtility::FileWithLineNumbers buildCopyMemberFunctionSource ();
  Rose::StringUtility::FileWithLineNumbers buildCopyMemberFunctionHeader ();

// DQ & JH (1/17/2006): Added support for building code to check pointers to IR nodes
  std::string buildPointerInMemoryPoolCheck ();

// AS (2/18/06): Added support for building code to return data member pointers to IR nodes
  std::string buildReturnDataMemberPointers ();
  std::string buildListIteratorString(std::string typeName, std::string variableName, std::string classNameString);

// DQ (4/30/2006): Added similar function to buildReturnDataMemberPointers() so that we could 
// return references to the pointers to IR nodes (required low level support for AST Merge).
  std::string buildProcessDataMemberReferenceToPointers ();
  std::string buildListIteratorStringForReferenceToPointers(std::string typeName, std::string variableName, std::string classNameString, bool traverse);

// DQ (3/7/2007): Building support for "long getChildIndex();" to be use for "bool isChild();" and other purposes.
  std::string buildChildIndex ();
  std::string buildListIteratorStringForChildIndex(std::string typeName, std::string variableName, std::string classNameString);

  virtual void show(size_t indent = 0) const;

  void consistencyCheck() const;
  void display ( const std::string& label = "" ) const;

/* JH (21/01/20005): Since in every method for building the source code for the StorageClases
   we need to build specific code for the data members of IRNode classes, we list all cases that
   we have to separate. Some of them can be removed, when ROSE does not longer contain pointers
   to stl vectors or lists. They are marked below, but may cause no trouble if they remain.
*/
// DQ (4/6/2006): New enum from Jochen's muilt file support.
  enum TypeEvaluation 
  {
    CHAR_POINTER,
    CONST_CHAR_POINTER,
    ATTACHEDPREPROCESSINGINFOTYPE,
    ROSE_HASH_MULTIMAP,
    ROSE_GRAPH_HASH_MULTIMAP,
    ROSE_GRAPH_DIRECTED_EDGE_HASH_MULTIMAP,
    ROSE_GRAPH_UNDIRECTED_EDGE_HASH_MULTIMAP,
    ROSE_GRAPH_NODE_EDGE_HASH_MULTIMAP,
    ROSE_GRAPH_INTEGER_NODE_HASH_MAP,
    ROSE_GRAPH_INTEGER_EDGE_HASH_MAP,
    ROSE_GRAPH_STRING_INTEGER_HASH_MULTIMAP,
    ROSE_GRAPH_INTEGER_PAIR_EDGE_HASH_MULTIMAP,
    ROSE_GRAPH_INTEGER_EDGE_HASH_MULTIMAP,
    SGCLASS_POINTER,
    ROSEATTRUBUTESLISTCONTAINER,
    SGCLASS_POINTER_LIST,
    SGCLASS_POINTER_VECTOR,
    SGCLASS_POINTER_VECTOR_NAMED_LIST,
    STL_CONTAINER,
    STL_SET,
    // DQ (4/30/2009): Added case of STL_MULTIMAP
    STL_MULTIMAP,
    STL_MAP,
    STRING,
    SGNAME,
    BIT_VECTOR,
    MODIFIERCLASS,
    MODIFIERCLASS_WITHOUTEASYSTORAGE,
    ASTATTRIBUTEMECHANISM,
    TO_HANDLE,
    OSTREAM,
    ENUM_TYPE,
    BASIC_DATA_TYPE,
    SKIP_TYPE,
    // should be no longer necessary after the implementation is changed to STL lists instead of pointers to lists
    SGCLASS_POINTER_LIST_POINTER
  };
  
  // JH (21/01/20005): method that evaluates the type string of a data member and returns the corresponding TypeEvaluation type
  // DQ (4/6/2006): Modified the function parameter as per Jochen's version
  TypeEvaluation evaluateType (std::string& varTypeString);
  
  // DQ (10/12/2014): output the name associated with the TypeEvaluation enum values.
  std::string typeEvaluationName ( TypeEvaluation x );

  /** C preprocessor condition for class declaration.
   * @{ */
  const std::string& getCppCondition() const;
  void setCppCondition(const std::string&);
  /** @} */

  /** Whether node supports boost::serialization. */
  bool isBoostSerializable() const;
  void isBoostSerializable(bool b);
  
  /* JH (10/28/2005): declaration of the source building methods for the storage classes
     concenrning the ast file IO. More about them one can find in the AstNodeClass.C file. They
     are called while the code generation of ROSETTA by the method 'buildStringForStorageClassSource'
     in the file grammar.C
  */
  std::string buildStorageClassHeader ();
  std::string buildStorageClassDeleteStaticDataSource ();
  std::string buildStorageClassArrangeStaticDataInOneBlockSource ();
  std::string buildStorageClassPickOutIRNodeDataSource ();
  std::string buildPointerInPoolCheck();
  std::string buildSourceForIRNodeStorageClassConstructor();
  std::string buildSourceForStoringStaticMembers ();
  std::string buildInitializationForStaticMembers ();
  std::string buildStaticDataConstructorSource();
  std::string buildStorageClassWriteStaticDataToFileSource () ;
  std::string buildStorageClassReadStaticDataFromFileSource ();
  bool hasMembersThatAreStoredInEasyStorageClass();
  bool hasStaticMembers ();
  
  // DQ (4/6/2006): Added these to match Jochen's new version
  std::string buildStaticDataMemberList();
  std::string buildStaticDataMemberListSetStaticData();
  std::string buildStaticDataMemberListDeleteStaticData();
  std::string buildStaticDataMemberListConstructor();
  std::string buildAccessFunctionsForStaticDataMember();
  std::string buildAccessFunctionsForStaticDataMemberSource();
  std::string buildStaticDataMemberListOfStorageClass();
  std::string buildStaticDataWriteEasyStorageDataToFileSource();
  std::string buildStaticDataReadEasyStorageDataFromFileSource();
  std::string buildStaticDataArrangeEasyStorageInOnePoolSource();
  std::string buildStaticDataDeleteEasyStorageMemoryPoolSource();
  
  // DQ (5/18/2007): support for documentation to handle mapping to KDM
  std::string outputClassesAndFields();
  
  // DQ (10/4/2014): Support for ATerms.
  std::string buildAtermSupport();
  
  // MS (5/27/2015)
  std::string outputFields();

 public:
  // MS (5/25/2016)
  void setGenerateEssentialDataMembersConstructorImplementation(bool);
  void setGenerateEnforcedDefaultConstructorImplementation(bool);
  bool getGenerateEssentialDataMembersConstructorImplementation();
  bool getGenerateEnforcedDefaultConstructorImplementation();
 private:
  bool generateEssentialDataMembersConstructorImplementation;
  bool generateEnforcedDefaultConstructorImplementation;
};

#endif
