#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TCanvas.h"


void wei_test()
{
	std::unique_ptr<TFile> file( TFile::Open("/exp/dune/data/users/psala/vbox/vbox_public/vbox_root_side001_Out.root"));

	TTree *fheader;
	TTree *fhits;

	TChain * hchain = new TChain("HitsTree","");
        hchain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_root_side001_Out.root/HitsTree");
        hchain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_root_side002_Out.root/HitsTree");
        hchain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_root_sideb001_Out.root/HitsTree");
        hchain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_root_sideb002_Out.root/HitsTree");
        hchain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_root_sidec001_Out.root/HitsTree");
        hchain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_root_sidec002_Out.root/HitsTree");
        fhits = hchain;
        TChain * chain = new TChain("HeaderTree","");
        chain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_root_side001_Out.root/HeaderTree");
        chain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_root_side002_Out.root/HeaderTree");
        chain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_root_sideb001_Out.root/HeaderTree");
        chain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_root_sideb002_Out.root/HeaderTree");
        chain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_root_sidec001_Out.root/HeaderTree");
        chain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_root_sidec002_Out.root/HeaderTree");
        fheader = chain;

	const Int_t MAXHITS = 400000;
	const Int_t MAXINEHITS = 400000;
	const Int_t MXS = 500000;
        
        Int_t           NIneHits;
        Int_t           TypeIne[MAXINEHITS];   //[NIneHits]
        Int_t           IdIne[MAXINEHITS];   //[NIneHits]
        Int_t           TrIne[MAXINEHITS];   //[NIneHits]
        Int_t           NTIneSec;
        Int_t           HitSecIne[MXS];   //[NTIneSec]
        Int_t           NSecIne[MAXINEHITS];   //[NIneHits]
        Int_t           FirstSec[MAXINEHITS];   //[NIneHits]
	Int_t           IdSecIne[MXS];   //[NTIneSec]

        // List of branches
        TBranch        *b_NIneHits;   //!
        TBranch        *b_TypeIne;   //!
        TBranch        *b_IdIne;   //!
        TBranch        *b_TrIne;   //!
        TBranch        *b_NTIneSec;   //!
        TBranch        *b_HitSecIne;   //!
        TBranch        *b_NSecIne;   //!
        TBranch        *b_FirstSec;   //!
	TBranch        *b_IdSecIne;   //!

	// These variables work fine        
	fhits->SetBranchAddress("NIneHits", &NIneHits, &b_NIneHits);
        fhits->SetBranchAddress("TypeIne", TypeIne, &b_TypeIne);
	fhits->SetBranchAddress("IdIne", IdIne, &b_IdIne);
        fhits->SetBranchAddress("TrIne", TrIne, &b_TrIne);
        fhits->SetBranchAddress("NTIneSec", &NTIneSec);//, &b_NTIneSec); // works without third argument
	fhits->SetBranchAddress("HitSecIne", HitSecIne, &b_HitSecIne);

	// These variables stop the program
	fhits->SetBranchAddress("NSecIne", NSecIne);//, &b_NSecIne); // doesn't work either way
	fhits->SetBranchAddress("FirstSec", FirstSec, &b_FirstSec);
       	fhits->SetBranchAddress("IdSecIne", IdSecIne, &b_IdSecIne);

	fhits->GetEntry(0);
	
	std::cout << "END" << std::endl;	
}



