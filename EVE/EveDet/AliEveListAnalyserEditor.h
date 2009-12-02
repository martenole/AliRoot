// Author: Benjamin Hess   06/11/2009

/*************************************************************************
 * Copyright (C) 2009, Alexandru Bercuci, Benjamin Hess.                 *
 * All rights reserved.                                                  *
 *************************************************************************/

#ifndef AliEveListAnalyserEditor_H
#define AliEveListAnalyserEditor_H


// TODO: Documentation
//////////////////////////////////////////////////////////////////////////
//                                                                      //
// AliEveListAnalyserEditor                                     //
//                                                                      //
// The AliEveListAnalyserEditor provides the graphical func-    //
// tionality for the AliEveListAnalyser. It creates the tabs    //
// and canvases, when they are needed and, as well, frees allocated     //
// memory on destruction (or if new events are loaded and thus some     //
// tabs are closed).                                                    //
// The function DrawHistos() accesses the temporary file created by the //
// AliEveListAnalyser and draws the desired data (the file will //
// be created within the call of ApplyMacros()). Have a look at this    //
// function to learn more about the structure of the file and how to    //
// access the data.                                                     //
//////////////////////////////////////////////////////////////////////////

#ifndef ROOT_TGedFrame
#include <TGedFrame.h>
#endif

#ifndef ROOT_TGFrame
#include <TGFrame.h>
#endif

class AliEveListAnalyser;
class AliTRDReconstructor;
class TCanvas;     
class TEveBrowser;           
class TEveGedEditor;
class TEveManager;
class TFile;
class TGButtonGroup;
class TGCheckButton;
class TGFileInfo;
class TGGroupFrame;
class TGHorizontal3DLine;
class TGHorizontalFrame;
class TGLabel;
class TGListBox;
class TGRadioButton;
class TGString;
class TGTab;
class TGTextButton;
class TGTextEntry;
class TGVerticalFrame;
class TH1;
class TMacroData;
class TMap;
class TMapIter;
class TTree;

class AliEveListAnalyserEditor: public TGedFrame
{
public:
  AliEveListAnalyserEditor(const TGWindow* p = 0, Int_t width = 170, Int_t height = 30,
		                       UInt_t options = kChildFrame, Pixel_t back = GetDefaultFrameBackground());
  virtual ~AliEveListAnalyserEditor();
  virtual void SetModel(TObject* obj);

  void    AddMacro(const Char_t* name, const Char_t* path = ".");  
  void    ApplyMacros();
  void    BrowseMacros();
  void    CloseTabs();
  void    DrawHistos();
  Int_t   GetNSelectedHistograms() const;
  void    HandleMacroPathSet();
  void    HandleNewEventLoaded();
  void    HandleTabChangedToIndex(Int_t);
  void    NewMacros();
  void    RemoveMacros();
  void    SaveMacroList(TMap* list);
  void    UpdateDataFromMacroListSelection();
  void    UpdateHistoList();
  void    UpdateMacroList();
  void    UpdateMacroListSelection(Int_t ind);
  
protected:
  AliEveListAnalyser* fM;                                               // Model object

  void InheritMacroList();                               
  void InheritStyle();                                    

private:
  AliEveListAnalyserEditor(const AliEveListAnalyserEditor&);            // Not implemented
  AliEveListAnalyserEditor& operator=(const AliEveListAnalyserEditor&); // Not implemented 

  TCanvas*          fHistoCanvas;            // Canvas for the histograms
  TGString*         fHistoCanvasName;        // Name of the histogram canvas

  TMap*             fInheritedMacroList;     // Stores the from the analyse object list inherited macro list

  Bool_t            fInheritSettings;        // Flag indicating, whether the macro list will be inherited from
                                             // the previously loaded analyse object list within the next call of SetModel

  TGVerticalFrame*   fMainFrame;             // Top frame for macro functionality.
  TGVerticalFrame*   fHistoFrame;            // Top frame for the histogram stuff
  TGVerticalFrame*   fHistoSubFrame;         // Frame for the histogram buttons themselves
  TGHorizontalFrame* fBrowseFrame;           // Frame for features corresponding to searching macros

  TGTextButton*   fbBrowse;                  // "Browse" button
  TGTextButton*   fbNew;                     // "New" button
  TGTextButton*   fbApplyMacros;             // "Apply macros" button
  TGTextButton*   fbRemoveMacros;            // "Remove macros" button
  TGTextButton*   fbDrawHisto;               // "Draw histogram" button
  TGTextEntry*    fteField;                  // Text field to insert macro path manually
  TGListBox*      ftlMacroList;              // To display the list of (process) macros
  TGListBox*      ftlMacroSelList;           // To display the list of (selection) macros

  TGFileInfo*     fFileInfo;                 // Holds data about opening macros
  Char_t**        fFileTypes;                // File types (for macros)

  // Some labels
  TGLabel* fLabel1;
  TGLabel* fLabel2;
  TGLabel* fLabel3;
  TGLabel* fLabel4;
     
  // Some lines
  TGHorizontal3DLine *fLine1;
  TGHorizontal3DLine *fLine2;
  TGHorizontal3DLine *fLine3;
  TGHorizontal3DLine *fLine4; 

  TGCheckButton** fCheckButtons;            // Check buttons for histograms

  // Help functions
  void SetDrawingToHistoCanvasTab();        
  void UpdateHistoCanvasTab();              

  ClassDef(AliEveListAnalyserEditor, 0);    // Editor for AliEveListAnalyser.
};


//////////////////////////////////////////////////////////////////////////
//                                                                      //
// AliEveGeneralMacroWizard                                             //
//                                                                      //
// Wizard for creating new macros.                                      //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

class TGTextEdit;
class TGComboBox;
class AliEveGeneralMacroWizard : public TGMainFrame
{
public:
  AliEveGeneralMacroWizard(const TGWindow* p = 0);
  void Create(Int_t type); //*SIGNAL*
  void Create(Char_t *pname); //*SIGNAL*
  void HandleCreate();

private:
  AliEveGeneralMacroWizard(const AliEveGeneralMacroWizard&);
  AliEveGeneralMacroWizard& operator=(const AliEveGeneralMacroWizard&);

  TGTextEntry *fTextName;
  TGTextEntry *fTextObjectType;
  TGComboBox  *fCombo;
  TGTextEdit  *fTextEdit;
  TGTextButton *fbCreate;                  // "Done" button
  TGTextButton *fbCancel;                  // "Cancel" button
  
  ClassDef(AliEveGeneralMacroWizard, 0);      // Helper class to create macro templates 
};

#endif
