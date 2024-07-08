#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TCanvas.h"


// Define a function with three parameters.
double fitf(double *x,double *par)
{
   	double fitval = par[0] + TMath::Exp(par[1] + x[0]*par[2]);
   	return fitval;
}


void pns_print()
{
	std::cout << "111" << std::endl;
	std::unique_ptr<TFile> file( TFile::Open("/exp/dune/data/users/psala/vbox/vbox_public/vbox_root_side001_Out.root"));

	int int_array[11] = {208,210,212,214,215,217,219,221,303,306,364};
	//int int_array[2] = {303,306};
	
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

	std::cout << "222" << std::endl;

	//auto fheader = file->Get<TTree>("HeaderTree");
	//auto fhits = file->Get<TTree>("HitsTree");

	const Int_t MAXHITS = 400000;
	const Int_t MAXINEHITS = 400000;
	const Int_t MXS = 500000;
        
        // Declaration of leaf types
        Int_t           RunNum;
        Int_t           EveNum;
        //Int_t           NIncHits;
        //Int_t           IdInc[MAXHITS];   //[NIncHits]
        //Int_t           IdParInc[MAXHITS];   //[NIncHits]
        //Int_t           TrInc[MAXHITS];   //[NIncHits]
        //Int_t           ParTrInc[MAXHITS];   //[NIncHits]
        //Int_t           IntParInc[MAXHITS];   //[NIncHits]
        //Int_t           RegInc[MAXHITS];   //[NIncHits]
        //Float_t         PosInc[MAXHITS][3];   //[NIncHits]
        //Float_t         PInc[MAXHITS][5];   //[NIncHits]
        //Float_t         TimeInc[MAXHITS];   //[NIncHits]
        //Int_t           NCalHits;
        //Int_t           WhCal[MAXHITS];   //[NCalHits]
        //Float_t         PosCal[MAXHITS][3];   //[NCalHits]
        //Float_t         EneCal[MAXHITS];   //[NCalHits]
        //Int_t           NCHitNCap;
        //Int_t           WhCNCap[MAXHITS];   //[NCHitNCap]
        //Float_t         PosCNCap[MAXHITS][3];   //[NCHitNCap]
        //Float_t         EneCNCap[MAXHITS];   //[NCHitNCap]
        //Int_t           NPheHits;
        //Float_t         Phe[MAXHITS];   //[NPheHits]
        //Int_t           PheTile[MAXHITS];   //[NPheHits]
        //Float_t         PheTime[MAXHITS];   //[NPheHits]
        //Float_t         TotPhe[4];
        //Int_t           NPheHitsNCap;
        //Float_t         PheNCap[MAXHITS];   //[NPheHitsNCap]
        //Int_t           PheTileNCap[MAXHITS];   //[NPheHitsNCap]
        //Float_t         PheTimeNCap[MAXHITS];   //[NPheHitsNCap]
        //Float_t         TotPheNCap[4];
        Int_t           NIneHits;
        Int_t           TypeIne[MAXINEHITS];   //[NIneHits]
        Int_t           IdIne[MAXINEHITS];   //[NIneHits]
        Int_t           TrIne[MAXINEHITS];   //[NIneHits]
        //Int_t           IdParIne[MAXINEHITS];   //[NIneHits]
        //Int_t           IntParIne[MAXHITS];   //[NIncHits]
        //Float_t         PIne[MAXINEHITS][5];   //[NIneHits]
        //Float_t         PosIne[MAXINEHITS][3];   //[NIneHits]
        //Float_t         TimeIne[MAXINEHITS];   //[NIneHits]
        Int_t           NSecIne[MAXINEHITS];   //[NIneHits]
        Int_t           FirstSec[MAXINEHITS];   //[NIneHits]
        Int_t           NTIneSec;
        Int_t           HitSecIne[MXS];   //[NTIneSec]
        Int_t           IdSecIne[MXS];   //[NTIneSec]
        //Int_t           ASecIne[MXS];   //[NTIneSec]
        //Int_t           ZSecIne[MXS];   //[NTIneSec]
        Int_t           TrSecIne[MXS];   //[NTIneSec]
        //Float_t         PSec[MXS][5];   //[NTIneSec]

        // List of branches
        TBranch        *b_RunNum;   //!
        TBranch        *b_EveNum;   //!
        //TBranch        *b_NIncHits;   //!
        //TBranch        *b_IdInc;   //!
        //TBranch        *b_IdParInc;   //!
        //TBranch        *b_TrInc;   //!
        //TBranch        *b_ParTrInc;   //!
        //TBranch        *b_IntParInc;   //!
        //TBranch        *b_RegInc;   //!
        //TBranch        *b_PosInc;   //!
        //TBranch        *b_PInc;   //!
        //TBranch        *b_TimeInc;   //!
        //TBranch        *b_NCalHits;   //!
        //TBranch        *b_WhCal;   //!
        //TBranch        *b_PosCal;   //!
        //TBranch        *b_EneCal;   //!
        //TBranch        *b_NCHitNCap;   //!
        //TBranch        *b_WhCNCap;   //!
        //TBranch        *b_PosCNCap;   //!
        //TBranch        *b_EneCNCap;   //!
        //TBranch        *b_NPheHits;   //!
        //TBranch        *b_Phe;   //!
        //TBranch        *b_PheTile;   //!
        //TBranch        *b_PheTime;   //!
        //TBranch        *b_TotPhe;   //!
        //TBranch        *b_NPheHitsNCap;   //!
        //TBranch        *b_PheNCap;   //!
        //TBranch        *b_PheTileNCap;   //!
        //TBranch        *b_PheTimeNCap;   //!
        //TBranch        *b_TotPheNCap;   //!
        TBranch        *b_NIneHits;   //!
        TBranch        *b_TypeIne;   //!
        TBranch        *b_IdIne;   //!
        TBranch        *b_TrIne;   //!
        //TBranch        *b_IdParIne;   //!
        //TBranch        *b_IntParIne;   //!
        //TBranch        *b_PIne;   //!
        //TBranch        *b_PosIne;   //!
        //TBranch        *b_TimeIne;   //!
        TBranch        *b_NSecIne;   //!
        TBranch        *b_FirstSec;   //!
        TBranch        *b_NTIneSec;   //!
        TBranch        *b_HitSecIne;   //!
        TBranch        *b_IdSecIne;   //!
        //TBranch        *b_ASecIne;   //!
        //TBranch        *b_ZSecIne;   //!
        TBranch        *b_TrSecIne;   //!
        //TBranch        *b_PSec;   //!
        ///////////////////////////////////////
        // Declaration of leaf types
        //   Int_t           RunNum;
        //   Int_t           EveNum;
  	/*
     	Int_t           ReacType;
        Int_t           IntType;
        Float_t         Vertex[3];
        Int_t           TargZ;
        Int_t           TargA;
        Int_t           Target;
        Int_t           Primary;
        Float_t         P_Primary[5];
        Int_t           ncaptures;
        Float_t         Edeptot;
        Float_t         phetot;
        Int_t           NumLep;
        Int_t           IdLep[1];   //[NumLep]
        Int_t           TrLep[1];   //[NumLep]
        Float_t         P_Lep[1][5];   //[NumLep]
        Int_t           NumHad;
        Int_t           IdHad[1];   //[NumHad]
        Int_t           TrHad[1];   //[NumHad]
        Float_t         P_Had[1][5];   //[NumHad]
        Int_t           NumPhot;
        Int_t           IdPhot[1];   //[NumPhot]
        Int_t           TrPhot[1];   //[NumPhot]
        Float_t         P_Phot[1][5];   //[NumPhot]
        Int_t           NumHeavy;
        Int_t           IdHeavy[1];   //[NumHeavy]
        Int_t           TrHeavy[1];   //[NumHeavy]
        Float_t         P_Heavy[1][5];   //[NumHeavy]
        Int_t           NumTracks;
        Int_t           IdTrack[1];   //[NumTracks]
        Int_t           Int_Track[1];   //[NumTracks]
        Float_t         Vtx_Track[1][3];   //[NumTracks]
        Int_t           Nsec_Track[1];   //[NumTracks]
        Float_t         Esec_Track[1][3];   //[NumTracks]
        Float_t         Psec_Track[1][3][3];   //[NumTracks]

        // List of branches
        //   TBranch        *b_RunNum;   //!
        //   TBranch        *b_EveNum;   //!
        TBranch        *b_ReacType;   //!
        TBranch        *b_IntType;   //!
        TBranch        *b_Vertex;   //!
        TBranch        *b_TargZ;   //!
        TBranch        *b_TargA;   //!
        TBranch        *b_Target;   //!
        TBranch        *b_Primary;   //!
        TBranch        *b_P_Primary;   //!
        TBranch        *b_ncaptures;   //!
        TBranch        *b_Edeptot;   //!
        TBranch        *b_phetot;   //!
        TBranch        *b_NumLep;   //!
        TBranch        *b_IdLep;   //!
        TBranch        *b_TrLep;   //!
        TBranch        *b_P_Lep;   //!
        TBranch        *b_NumHad;   //!
        TBranch        *b_IdHad;   //!
        TBranch        *b_TrHad;   //!
        TBranch        *b_P_Had;   //!
        TBranch        *b_NumPhot;   //!
        TBranch        *b_IdPhot;   //!
        TBranch        *b_TrPhot;   //!
        TBranch        *b_P_Phot;   //!
        TBranch        *b_NumHeavy;   //!
        TBranch        *b_IdHeavy;   //!
        TBranch        *b_TrHeavy;   //!
        TBranch        *b_P_Heavy;   //!
        TBranch        *b_NumTracks;   //!
        TBranch        *b_IdTrack;   //!
        TBranch        *b_Int_Track;   //!
        TBranch        *b_Vtx_Track;   //!
        TBranch        *b_Nsec_Track;   //!
        TBranch        *b_Esec_Track;   //!
        TBranch        *b_Psec_Track;   //!
	*/	

        /////////////
        //all in microseconds
       
        //TH1F* timeh1;
        //if (timeh1 != NULL )
        //{delete timeh1;}
        //if (timeh2 != nullptr ) {delete timeh2;}
        //if (tall != nullptr ) {delete tall;}
        //if (tc != nullptr ) {delete tc;}

	
	//TH1F* timeine208=new TH1F("timeine208","time smear",1200,0.,1200.);
	//TH1F* timeine210=new TH1F("timeine210","time smear",1200,0.,1200.);
	//TH1F* timeine212=new TH1F("timeine212","time smear",1200,0.,1200.);
	//TH1F* timeine214=new TH1F("timeine214","time smear",1200,0.,1200.);
	//TH1F* timeine215=new TH1F("timeine215","time smear",1200,0.,1200.);
	//TH1F* timeine217=new TH1F("timeine217","time smear",1200,0.,1200.);
	//TH1F* timeine219=new TH1F("timeine219","time smear",1200,0.,1200.);
	//TH1F* timeine221=new TH1F("timeine221","time smear",1200,0.,1200.);
	//TH1F* timeine303=new TH1F("timeine303","time smear",1200,0.,1200.);
	//TH1F* timeine306=new TH1F("timeine306","time smear",1200,0.,1200.);
	//TH1F* timeine364=new TH1F("timeine364","time smear",1200,0.,1200.);

	std::cout << "333" << std::endl;

	/*
        fhits->SetMakeClass(1);
        fheader->SetMakeClass(1);
        fheader->SetBranchAddress("RunNum", &RunNum, &b_RunNum);
	fheader->SetBranchAddress("EveNum", &EveNum, &b_EveNum);
        fheader->SetBranchAddress("Vertex", Vertex, &b_Vertex);
        fheader->SetBranchAddress("TargZ", &TargZ, &b_TargZ);
        fheader->SetBranchAddress("TargA", &TargA, &b_TargA);
        fheader->SetBranchAddress("Target", &Target, &b_Target);
        fheader->SetBranchAddress("Primary", &Primary, &b_Primary);
        fheader->SetBranchAddress("P_Primary", P_Primary, &b_P_Primary);
        fheader->SetBranchAddress("ncaptures", &ncaptures, &b_ncaptures);
        fheader->SetBranchAddress("Edeptot", &Edeptot, &b_Edeptot);
        fheader->SetBranchAddress("phetot", &phetot, &b_phetot);
        fheader->SetBranchAddress("NumLep", &NumLep, &b_NumLep);
        fheader->SetBranchAddress("IdLep", &IdLep, &b_IdLep);
        fheader->SetBranchAddress("TrLep", &TrLep, &b_TrLep);
        fheader->SetBranchAddress("P_Lep", &P_Lep, &b_P_Lep);
        fheader->SetBranchAddress("NumHad", &NumHad, &b_NumHad);
        fheader->SetBranchAddress("IdHad", IdHad, &b_IdHad);
        fheader->SetBranchAddress("TrHad", TrHad, &b_TrHad);
        fheader->SetBranchAddress("P_Had", P_Had, &b_P_Had);
        fheader->SetBranchAddress("NumPhot", &NumPhot, &b_NumPhot);
        fheader->SetBranchAddress("IdPhot", &IdPhot, &b_IdPhot);
        fheader->SetBranchAddress("TrPhot", &TrPhot, &b_TrPhot);
        fheader->SetBranchAddress("P_Phot", &P_Phot, &b_P_Phot);
        fheader->SetBranchAddress("NumHeavy", &NumHeavy, &b_NumHeavy);
        fheader->SetBranchAddress("IdHeavy", &IdHeavy, &b_IdHeavy);
        fheader->SetBranchAddress("TrHeavy", &TrHeavy, &b_TrHeavy);
        fheader->SetBranchAddress("P_Heavy", &P_Heavy, &b_P_Heavy);
        fheader->SetBranchAddress("NumTracks", &NumTracks, &b_NumTracks);
        fheader->SetBranchAddress("IdTrack", IdTrack, &b_IdTrack);
        fheader->SetBranchAddress("Int_Track", Int_Track, &b_Int_Track);
        fheader->SetBranchAddress("Vtx_Track", Vtx_Track, &b_Vtx_Track);
        fheader->SetBranchAddress("Nsec_Track", Nsec_Track, &b_Nsec_Track);
        fheader->SetBranchAddress("Esec_Track", Esec_Track, &b_Esec_Track);
        fheader->SetBranchAddress("Psec_Track", Psec_Track, &b_Psec_Track);
       	*/ 
        fhits->SetBranchAddress("RunNum", &RunNum, &b_RunNum);
	fhits->SetBranchAddress("EveNum", &EveNum, &b_EveNum);
        /*
	fhits->SetBranchAddress("NIncHits", &NIncHits, &b_NIncHits);
        fhits->SetBranchAddress("IdInc", IdInc, &b_IdInc);
        fhits->SetBranchAddress("IdParInc", IdParInc, &b_IdParInc);
        fhits->SetBranchAddress("TrInc", TrInc, &b_TrInc);
        fhits->SetBranchAddress("ParTrInc", ParTrInc, &b_ParTrInc);
        fhits->SetBranchAddress("IntParInc", IntParInc, &b_IntParInc);
	//fhits->SetBranchAddress("RegInc", RegInc, &b_RegInc);
	*/
	//fhits->SetBranchAddress("PosInc", PosInc, &b_PosInc);
	//fhits->SetBranchAddress("PInc", PInc, &b_PInc);
	//fhits->SetBranchAddress("TimeInc", TimeInc, &b_TimeInc);
	//fhits->SetBranchAddress("NCalHits", &NCalHits, &b_NCalHits);
	//fhits->SetBranchAddress("WhCal", WhCal, &b_WhCal);
	//fhits->SetBranchAddress("PosCal", PosCal, &b_PosCal);
	//fhits->SetBranchAddress("EneCal", EneCal, &b_EneCal);
	//fhits->SetBranchAddress("NCHitNCap", &NCHitNCap, &b_NCHitNCap);
	//fhits->SetBranchAddress("WhCNCap", WhCNCap, &b_WhCNCap);
	//fhits->SetBranchAddress("PosCNCap", PosCNCap, &b_PosCNCap);
	//fhits->SetBranchAddress("EneCNCap", EneCNCap, &b_EneCNCap);
	//fhits->SetBranchAddress("NPheHits", &NPheHits, &b_NPheHits);
	//fhits->SetBranchAddress("Phe", Phe, &b_Phe);
	//fhits->SetBranchAddress("PheTile", PheTile, &b_PheTile);
	//fhits->SetBranchAddress("PheTime", PheTime, &b_PheTime); 
	//fhits->SetBranchAddress("TotPhe", TotPhe, &b_TotPhe); 
	
	//fhits->SetBranchAddress("NPheHitsNCap", &NPheHitsNCap, &b_NPheHitsNCap);
        //fhits->SetBranchAddress("PheNCap", PheNCap, &b_PheNCap);
        //fhits->SetBranchAddress("PheTileNCap", PheTileNCap, &b_PheTileNCap);
        //fhits->SetBranchAddress("PheTimeNCap", PheTimeNCap, &b_PheTimeNCap);
        //fhits->SetBranchAddress("TotPheNCap", TotPheNCap, &b_TotPheNCap);
        fhits->SetBranchAddress("NIneHits", &NIneHits, &b_NIneHits);
        fhits->SetBranchAddress("TypeIne", TypeIne, &b_TypeIne);
	fhits->SetBranchAddress("IdIne", IdIne, &b_IdIne);
        fhits->SetBranchAddress("TrIne", TrIne, &b_TrIne);
        //fhits->SetBranchAddress("IdParIne", IdParIne, &b_IdParIne);
        //fhits->SetBranchAddress("IntParIne", IntParIne, &b_IntParIne);
        //fhits->SetBranchAddress("PIne", PIne, &b_PIne);
        //fhits->SetBranchAddress("PosIne", PosIne, &b_PosIne);
        //fhits->SetBranchAddress("TimeIne", TimeIne, &b_TimeIne);
        //fhits->SetBranchAddress("NSecIne", NSecIne, &b_NSecIne);
        //fhits->SetBranchAddress("FirstSec", FirstSec, &b_FirstSec);
        fhits->SetBranchAddress("NTIneSec", &NTIneSec, &b_NTIneSec);
        //fhits->SetBranchAddress("HitSecIne", HitSecIne, &b_HitSecIne);
        //fhits->SetBranchAddress("IdSecIne", IdSecIne, &b_IdSecIne);
        //fhits->SetBranchAddress("ASecIne", ASecIne, &b_ASecIne);
        //fhits->SetBranchAddress("ZSecIne", ZSecIne, &b_ZSecIne);
        fhits->SetBranchAddress("TrSecIne", TrSecIne, &b_TrSecIne);
        //fhits->SetBranchAddress("PSec", PSec, &b_PSec);
		
	std::cout << "444" << std::endl;

	Long64_t nentries_hit = 10;//fhits->GetEntries();
	for (Long64_t i=0; i<nentries_hit; i++)
        {
		fhits->GetEntry(i);
		std::cout << NIneHits << std::endl;	
		
		std::cout << "TypeIne" << std::endl;	
		for(int a=0; a<NIneHits; a++)
		{
			std::cout << TypeIne[a] << "  ";		
		}
		std::cout << std::endl;

		std::cout << "IdIne" << std::endl;
		for(int b=0; b<NIneHits; b++)
                {
                        std::cout << IdIne[b] << "  ";
                }
                std::cout << std::endl;
	
		std::cout << "TrIne" << std::endl;
		for(int c=0; c<NIneHits; c++)
                {
                        std::cout << TrIne[c] << "  ";
                }
                std::cout << "\n" << std::endl;

		/*	
		std::cout << NTIneSec << std::endl;

                std::cout << "NSecIne" << std::endl;
                for(int d=0; d<NTIneSec; d++)
                {
                        std::cout << NSecIne[d] << "  ";
                }
                std::cout << std::endl;

                std::cout << "FirstSec" << std::endl;
                for(int e=0; e<NTIneSec; e++)
                {
                        std::cout << FirstSec[e] << "  ";
                }
                std::cout << std::endl;

                std::cout << "HitSecIne" << std::endl;
                for(int f=0; f<NTIneSec; f++)
                {
                        std::cout << HitSecIne[f] << "  ";
                }
                std::cout << std::endl;
		
		std::cout << "IdSecIne" << std::endl;
                for(int g=0; g<NTIneSec; g++)
                {
                        std::cout << IdSecIne[g] << "  ";
                }
                std::cout << std::endl;

		std::cout << "TrSecIne" << std::endl;
                for(int h=0; h<NTIneSec; h++)
                {
                        std::cout << TrSecIne[h] << "  ";
                }
                std::cout << "\n" << std::endl;
		*/
	}
	
	std::cout << "END" << std::endl;	

	/*
	Long64_t nentries_head = fheader->GetEntries();
	for (Long64_t i=0; i<nentries_head; i++)
        {
                fheader->GetEntry(i);

                //std::cout << "Entry " << i << std::endl;

	}
	*/
	// Create a TF1 object using the fitf function. The last three parameters
	// specify the range and the number of parameters for the function.
}



