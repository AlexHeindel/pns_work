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


void pns_plot_jul24()
{
	std::unique_ptr<TFile> file( TFile::Open("/exp/dune/data/users/psala/vbox/vbox_public/vbox_root_side001_Out.root"));
	
	TTree *fheader;
	TTree *fhits;

	TChain * hchain = new TChain("HitsTree","");
      	hchain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_side001_Out.root/HitsTree");
      	hchain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_side002_Out.root/HitsTree");
      	hchain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sideb001_Out.root/HitsTree");
      	hchain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sideb002_Out.root/HitsTree");
      	hchain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sideb003_Out.root/HitsTree");
      	hchain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sideb004_Out.root/HitsTree");
      	hchain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sideb005_Out.root/HitsTree");
      	hchain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sidec001_Out.root/HitsTree");
      	hchain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sidec002_Out.root/HitsTree");
      	hchain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sidec003_Out.root/HitsTree");
      	hchain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sidec004_Out.root/HitsTree");
      	hchain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sidec005_Out.root/HitsTree");
      	hchain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sided001_Out.root/HitsTree");
      	hchain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sided002_Out.root/HitsTree");
      	hchain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sided003_Out.root/HitsTree");
      	hchain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sided004_Out.root/HitsTree");
      	hchain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sided005_Out.root/HitsTree");
      	fhits = hchain;
	TChain * chain = new TChain("HeaderTree","");
      	chain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_side001_Out.root/HeaderTree");
      	chain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_side002_Out.root/HeaderTree");
      	chain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sideb001_Out.root/HeaderTree");
      	chain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sideb002_Out.root/HeaderTree");
      	chain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sideb003_Out.root/HeaderTree");
      	chain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sideb004_Out.root/HeaderTree");
      	chain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sideb005_Out.root/HeaderTree");
      	chain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sidec001_Out.root/HeaderTree");
      	chain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sidec002_Out.root/HeaderTree");
      	chain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sidec003_Out.root/HeaderTree");
      	chain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sidec004_Out.root/HeaderTree");
      	chain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sidec005_Out.root/HeaderTree");
      	chain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sided001_Out.root/HeaderTree");
      	chain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sided002_Out.root/HeaderTree");
      	chain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sided003_Out.root/HeaderTree");
      	chain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sided004_Out.root/HeaderTree");
      	chain->Add("/exp/dune/data/users/psala/vbox/vbox_public/vbox_jul24_sided005_Out.root/HeaderTree");
      	fheader = chain;

	//auto fheader = file->Get<TTree>("HeaderTree");
	//auto fhits = file->Get<TTree>("HitsTree");

	const Int_t MAXHITS = 4000;
	const Int_t MAXINEHITS = 4000;
	const Int_t MXS = 5000;
        
        // Declaration of leaf types
        Int_t           RunNum;
        Int_t           EveNum;
        Int_t           NIncHits;
        Int_t           IdInc[MAXHITS];   //[NIncHits]
        Int_t           IdParInc[MAXHITS];   //[NIncHits]
        Int_t           TrInc[MAXHITS];   //[NIncHits]
        Int_t           ParTrInc[MAXHITS];   //[NIncHits]
        Int_t           IntParInc[MAXHITS];   //[NIncHits]
        Int_t           RegInc[MAXHITS];   //[NIncHits]
        Float_t         PosInc[MAXHITS][3];   //[NIncHits]
        Float_t         PInc[MAXHITS][5];   //[NIncHits]
        Float_t         TimeInc[MAXHITS];   //[NIncHits]
        Int_t           NCalHits;
        Int_t           WhCal[MAXHITS];   //[NCalHits]
        Float_t         PosCal[MAXHITS][3];   //[NCalHits]
        Float_t         EneCal[MAXHITS];   //[NCalHits]
        Int_t           NCHitNCap;
        Int_t           WhCNCap[MAXHITS];   //[NCHitNCap]
        Float_t         PosCNCap[MAXHITS][3];   //[NCHitNCap]
        Float_t         EneCNCap[MAXHITS];   //[NCHitNCap]
        Int_t           NPheHits;
        Float_t         Phe[MAXHITS];   //[NPheHits]
        Int_t           PheTile[MAXHITS];   //[NPheHits]
        Float_t         PheTime[MAXHITS];   //[NPheHits]
        Float_t         TotPhe[4];
        Int_t           NPheHitsNCap;
        Float_t         PheNCap[MAXHITS];   //[NPheHitsNCap]
        Int_t           PheTileNCap[MAXHITS];   //[NPheHitsNCap]
        Float_t         PheTimeNCap[MAXHITS];   //[NPheHitsNCap]
        Float_t         TotPheNCap[4];
        Int_t           NIneHits;
        Int_t           TypeIne[MAXINEHITS];   //[NIneHits]
        Int_t           IdIne[MAXINEHITS];   //[NIneHits]
        Int_t           TrIne[MAXINEHITS];   //[NIneHits]
        Int_t           IdParIne[MAXINEHITS];   //[NIneHits]
        Int_t           IntParIne[MAXHITS];   //[NIncHits]
        Float_t         PIne[MAXINEHITS][5];   //[NIneHits]
        Float_t         PosIne[MAXINEHITS][3];   //[NIneHits]
        Float_t         TimeIne[MAXINEHITS];   //[NIneHits]
        Int_t           NSecIne[MAXINEHITS];   //[NIneHits]
        Int_t           FirstSec[MAXINEHITS];   //[NIneHits]
        Int_t           NTIneSec;
        Int_t           HitSecIne[MXS];   //[NTIneSec]
        Int_t           IdSecIne[MXS];   //[NTIneSec]
        Int_t           ASecIne[MXS];   //[NTIneSec]
        Int_t           ZSecIne[MXS];   //[NTIneSec]
        Int_t           TrSecIne[MXS];   //[NTIneSec]
        Float_t         PSec[MXS][5];   //[NTIneSec]

        // List of branches
        TBranch        *b_RunNum;   //!
        TBranch        *b_EveNum;   //!
        TBranch        *b_NIncHits;   //!
        TBranch        *b_IdInc;   //!
        TBranch        *b_IdParInc;   //!
        TBranch        *b_TrInc;   //!
        TBranch        *b_ParTrInc;   //!
        TBranch        *b_IntParInc;   //!
        TBranch        *b_RegInc;   //!
        TBranch        *b_PosInc;   //!
        TBranch        *b_PInc;   //!
        TBranch        *b_TimeInc;   //!
        TBranch        *b_NCalHits;   //!
        TBranch        *b_WhCal;   //!
        TBranch        *b_PosCal;   //!
        TBranch        *b_EneCal;   //!
        TBranch        *b_NCHitNCap;   //!
        TBranch        *b_WhCNCap;   //!
        TBranch        *b_PosCNCap;   //!
        TBranch        *b_EneCNCap;   //!
        TBranch        *b_NPheHits;   //!
        TBranch        *b_Phe;   //!
        TBranch        *b_PheTile;   //!
        TBranch        *b_PheTime;   //!
        TBranch        *b_TotPhe;   //!
        TBranch        *b_NPheHitsNCap;   //!
        TBranch        *b_PheNCap;   //!
        TBranch        *b_PheTileNCap;   //!
        TBranch        *b_PheTimeNCap;   //!
        TBranch        *b_TotPheNCap;   //!
        TBranch        *b_NIneHits;   //!
        TBranch        *b_TypeIne;   //!
        TBranch        *b_IdIne;   //!
        TBranch        *b_TrIne;   //!
        TBranch        *b_IdParIne;   //!
        TBranch        *b_IntParIne;   //!
        TBranch        *b_PIne;   //!
        TBranch        *b_PosIne;   //!
        TBranch        *b_TimeIne;   //!
        TBranch        *b_NSecIne;   //!
        TBranch        *b_FirstSec;   //!
        TBranch        *b_NTIneSec;   //!
        TBranch        *b_HitSecIne;   //!
        TBranch        *b_IdSecIne;   //!
        TBranch        *b_ASecIne;   //!
        TBranch        *b_ZSecIne;   //!
        TBranch        *b_TrSecIne;   //!
        TBranch        *b_PSec;   //!
        ///////////////////////////////////////
        // Declaration of leaf types
        //   Int_t           RunNum;
        //   Int_t           EveNum;
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

        /////////////
        //all in microseconds
       
        //TH1F* timeh1;
        //if (timeh1 != NULL )
        //{delete timeh1;}
        //if (timeh2 != nullptr ) {delete timeh2;}
        //if (tall != nullptr ) {delete tall;}
        //if (tc != nullptr ) {delete tc;}
       
	TH1F* timeh1=new TH1F("timeh1","no smear",1200,0.,1200.);
	TH1F* timeh2=new TH1F("timeh2","time smear",1200,0.,1200.);
 	TH1F* timeh3=new TH1F("timeh3","time smear all bunches",1200,0.,1200.);
	TH1F* tall= new TH1F("tall","convoluted",75000,0.,1200.);
  	TH1F* tcglob= new TH1F("tcglob","convoluted",75000,0.,1200.);
  	TH1F* tcompact= new TH1F("tcompact","convoluted",1200,0.,1200.);	
	TH1F* tc = new TH1F("tc","convoluted",75000,0.,1200.);
        tc->GetXaxis()->SetRange(1,75000);

	TH1F *harray[4];
        auto hs = new THStack("hs","");

        for(int h = 0; h<4; h++)
        {
                TString name = Form("timetile%d",h);
                harray[h] = new TH1F(name, "time smear", 1200,0.,1200);
        }
	
	TH1F* timeh1NCap=new TH1F("timeh1NCap","no smear",1200,0.,1200.);
	TH1F* timeh2NCap=new TH1F("timeh2NCap","time smear",1200,0.,1200.);
 	TH1F* timeh3NCap=new TH1F("timeh3NCap","time smear all bunches",1200,0.,1200.);
	TH1F* tallNCap= new TH1F("tallNCap","convoluted",75000,0.,1200.);
  	TH1F* tcglobNCap= new TH1F("tcglobNCap","convoluted",75000,0.,1200.);
  	TH1F* tcompactNCap= new TH1F("tcompactNCap","convoluted",1200,0.,1200.);	
	TH1F* tcNCap = new TH1F("tcNCap","convoluted",75000,0.,1200.);
        tcNCap->GetXaxis()->SetRange(1,75000);

	TH1F *harrayNCap[4];

        for(int h = 0; h<4; h++)
        {
                TString name = Form("timetile%dNCap",h);
                harrayNCap[h] = new TH1F(name, "time smear", 1200,0.,1200);
        }

	TH1F* posinex=new TH1F("posinex","position of hit",200,-100.,100.);
	TH1F* posiney=new TH1F("posiney","position of hit",400,-200.,200.);
	TH1F* posinez=new TH1F("posinez","position of hit",400,-200.,200.);
	TH1F* posinex303=new TH1F("posinex303","position of hit",200,-100.,100.);
	TH1F* posiney303=new TH1F("posiney303","position of hit",400,-200.,200.);
	TH1F* posinez303=new TH1F("posinez303","position of hit",400,-200.,200.);
	TH1F* posinex306=new TH1F("posinex306","position of hit",200,-100.,100.);
	TH1F* posiney306=new TH1F("posiney306","position of hit",400,-200.,200.);
	TH1F* posinez306=new TH1F("posinez306","position of hit",400,-200.,200.);

	TH1F* mominex=new TH1F("mominex","x momentum of hit",100,-0.04,0.04);
	TH1F* mominey=new TH1F("mominey","y momentum of hit",100,-0.04,0.04);
	TH1F* mominez=new TH1F("mominez","z momentum of hit",100,-0.04,0.04);
	TH1F* toteine=new TH1F("toteine","total energy of hit",100,0.,1.);
	TH1F* kineine=new TH1F("kineine","kinetic energy of incoming particle",100,0.,.01);
	TH1F* mominex303=new TH1F("mominex303","x momentum of hit",100,-0.08,0.08);
	TH1F* mominey303=new TH1F("mominey303","y momentum of hit",100,-0.08,0.08);
	TH1F* mominez303=new TH1F("mominez303","z momentum of hit",100,-0.08,0.08);
	TH1F* toteine303=new TH1F("toteine303","total energy of hit",100,0.94,0.944);
	TH1F* kineine303=new TH1F("kineine303","kinetic energy of incoming particle",100,0.,.0015);
	TH1F* mominex306=new TH1F("mominex306","x momentum of hit",100,-0.000000001,0.000000001);
	TH1F* mominey306=new TH1F("mominey306","y momentum of hit",100,-0.000000001,0.000000001);
	TH1F* mominez306=new TH1F("mominez306","z momentum of hit",100,-0.000000001,0.000000001);
	TH1F* toteine306=new TH1F("toteine306","total energy of hit",100,0.939,0.941);
	TH1F* kineine306=new TH1F("kineine306","kinetic energy of incoming particle",100,0.,.000000001);

	TH1F* posinexgamma=new TH1F("posinexgamma","position of hit",200,-100.,100.);
	TH1F* posineygamma=new TH1F("posineygamma","position of hit",400,-200.,200.);
	TH1F* posinezgamma=new TH1F("posinezgamma","position of hit",400,-200.,200.);
	TH1F* mominexgamma=new TH1F("mominexgamma","x momentum of hit",100,-0.04,0.04);
	TH1F* momineygamma=new TH1F("momineygamma","y momentum of hit",100,-0.04,0.04);
	TH1F* mominezgamma=new TH1F("mominezgamma","z momentum of hit",100,-0.04,0.04);
	TH1F* toteinegamma=new TH1F("toteinegamma","total energy of hit",100,0.,.01);
	TH1F* kineinegamma=new TH1F("kineinegamma","kinetic energy of incoming particle",100,0.,.01);
	
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
        fhits->SetBranchAddress("NIncHits", &NIncHits, &b_NIncHits);
        fhits->SetBranchAddress("IdInc", IdInc, &b_IdInc);
        fhits->SetBranchAddress("IdParInc", IdParInc, &b_IdParInc);
        fhits->SetBranchAddress("TrInc", TrInc, &b_TrInc);
        fhits->SetBranchAddress("ParTrInc", ParTrInc, &b_ParTrInc);
        fhits->SetBranchAddress("IntParInc", IntParInc, &b_IntParInc);
	fhits->SetBranchAddress("RegInc", RegInc, &b_RegInc);
	fhits->SetBranchAddress("PosInc", PosInc, &b_PosInc);
	fhits->SetBranchAddress("PInc", PInc, &b_PInc);
	fhits->SetBranchAddress("TimeInc", TimeInc, &b_TimeInc);
	fhits->SetBranchAddress("NCalHits", &NCalHits, &b_NCalHits);
	fhits->SetBranchAddress("WhCal", WhCal, &b_WhCal);
	fhits->SetBranchAddress("PosCal", PosCal, &b_PosCal);
	fhits->SetBranchAddress("EneCal", EneCal, &b_EneCal);
	fhits->SetBranchAddress("NCHitNCap", &NCHitNCap, &b_NCHitNCap);
	fhits->SetBranchAddress("WhCNCap", WhCNCap, &b_WhCNCap);
	fhits->SetBranchAddress("PosCNCap", PosCNCap, &b_PosCNCap);
	fhits->SetBranchAddress("EneCNCap", EneCNCap, &b_EneCNCap);
	fhits->SetBranchAddress("NPheHits", &NPheHits, &b_NPheHits);
	fhits->SetBranchAddress("Phe", Phe, &b_Phe);
	fhits->SetBranchAddress("PheTile", PheTile, &b_PheTile);
	fhits->SetBranchAddress("PheTime", PheTime, &b_PheTime); 
	fhits->SetBranchAddress("TotPhe", TotPhe, &b_TotPhe); 
	
	fhits->SetBranchAddress("NPheHitsNCap", &NPheHitsNCap, &b_NPheHitsNCap);
        fhits->SetBranchAddress("PheNCap", PheNCap, &b_PheNCap);
        fhits->SetBranchAddress("PheTileNCap", PheTileNCap, &b_PheTileNCap);
        fhits->SetBranchAddress("PheTimeNCap", PheTimeNCap, &b_PheTimeNCap);
        fhits->SetBranchAddress("TotPheNCap", TotPheNCap, &b_TotPheNCap);
        fhits->SetBranchAddress("NIneHits", &NIneHits, &b_NIneHits);
        fhits->SetBranchAddress("TypeIne", TypeIne, &b_TypeIne);
        
	fhits->SetBranchAddress("IdIne", IdIne, &b_IdIne);
        fhits->SetBranchAddress("TrIne", TrIne, &b_TrIne);
        fhits->SetBranchAddress("IdParIne", IdParIne, &b_IdParIne);
        fhits->SetBranchAddress("IntParIne", IntParIne, &b_IntParIne);
        fhits->SetBranchAddress("PIne", PIne, &b_PIne);
        fhits->SetBranchAddress("PosIne", PosIne, &b_PosIne);
        fhits->SetBranchAddress("TimeIne", TimeIne, &b_TimeIne);
        fhits->SetBranchAddress("NSecIne", NSecIne, &b_NSecIne);
        fhits->SetBranchAddress("FirstSec", FirstSec, &b_FirstSec);
        fhits->SetBranchAddress("NTIneSec", &NTIneSec, &b_NTIneSec);
        fhits->SetBranchAddress("HitSecIne", HitSecIne, &b_HitSecIne);
        fhits->SetBranchAddress("IdSecIne", IdSecIne, &b_IdSecIne);
        fhits->SetBranchAddress("ASecIne", ASecIne, &b_ASecIne);
        fhits->SetBranchAddress("ZSecIne", ZSecIne, &b_ZSecIne);
        fhits->SetBranchAddress("TrSecIne", TrSecIne, &b_TrSecIne);
        fhits->SetBranchAddress("PSec", PSec, &b_PSec);

	TRandom *myran       = new TRandom();
	Double_t rr=0.0, rr2=0.0, offset1=0.0, offset2=0.0;
	Double_t thr1=10.0; //total phe on 1 tile to get above threshold
   	Double_t thr2=14.5*5.; // 5 phe
   	Double_t effi=0.3;

	int num_303 = 0;
	int num_306 = 0;
	int sum_303 = 0;
	int sum_306 = 0;
	int total_neut_int = 0;	
	int multi_sum = 0;

	Double_t response[115];
	TFile* rfile= TFile::Open("sample.root");

	TCanvas* h = nullptr;
	rfile->GetObject("cpers_s",h);
 	TH1D *avg = (TH1D*)h->GetPrimitive("haverage_s_Ch0");
        for (int i=0; i<115;  i++)
	{
        	response[i]=avg->GetBinContent(i+388);
        }
	
	Long64_t nentries_hit = fhits->GetEntries();
	for (Long64_t i=0; i<nentries_hit; i++)
        {
		fhits->GetEntry(i);
	
		num_303 = 0;
		num_306 = 0;

		for(int k=0; k<NIneHits; k++)
                {
                	if(TypeIne[k] == 303 && IdIne[k] == 2112)
                        {
                        	num_303++;
                        	sum_303++;
				posinex303->Fill(PosIne[k][0]);
				posiney303->Fill(PosIne[k][1]);
				posinez303->Fill(PosIne[k][2]);
				mominex303->Fill(PIne[k][0]);
				mominey303->Fill(PIne[k][1]);
				mominez303->Fill(PIne[k][2]);
				toteine303->Fill(PIne[k][3]);
				kineine303->Fill(PIne[k][4]);
                        }
                	if(TypeIne[k] == 306 && IdIne[k] == 2112)
                        {
				if (PIne[k][4] != 0)
				{
        				//std::cout << PIne[k][4] << std::endl;
	                	}
				num_306++;
                        	sum_306++;
				posinex306->Fill(PosIne[k][0]);
				posiney306->Fill(PosIne[k][1]);
				posinez306->Fill(PosIne[k][2]);
				mominex306->Fill(PIne[k][0]);
				mominey306->Fill(PIne[k][1]);
				mominez306->Fill(PIne[k][2]);
				toteine306->Fill(PIne[k][3]);
				kineine306->Fill(PIne[k][4]);
                        }
                	if(IdIne[k] == 22)// && TypeIne[k] == 217 && PIne[k][4] > 0.008)
			{
				posinexgamma->Fill(PosIne[k][0]);
				posineygamma->Fill(PosIne[k][1]);
				posinezgamma->Fill(PosIne[k][2]);
				mominexgamma->Fill(PIne[k][0]);
				momineygamma->Fill(PIne[k][1]);
				mominezgamma->Fill(PIne[k][2]);
				toteinegamma->Fill(PIne[k][3]);
				kineinegamma->Fill(PIne[k][4]);  
			}
	
			posinex->Fill(PosIne[k][0]);
			posiney->Fill(PosIne[k][1]);
			posinez->Fill(PosIne[k][2]);
			mominex->Fill(PIne[k][0]);
			mominey->Fill(PIne[k][1]);
			mominez->Fill(PIne[k][2]);
			toteine->Fill(PIne[k][3]);
			kineine->Fill(PIne[k][4]);
                }	

		if (num_303 > 0 || num_306 > 0)
		{
			total_neut_int++;
		}

		if (num_303 > 0 && num_306 > 0)
		{
			/*
			std::cout << "303: " << num_303	<< "  num_306: " << num_306 << std::endl;
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
			*/
			sum_303--;
			sum_306--;
			multi_sum++;		
		}
	
		if (TotPhe[2]*effi>thr1)
		{
                	rr2=myran->Rndm();
                	rr2=rr2*5;
                	rr2=Int_t(rr2)*80.0; //-280.0;
                	rr=myran->Rndm();
                	offset2=rr*60.0+rr2;
                	offset1=offset2-280.0;
                	for (int iph=0; iph<NPheHits; iph++)
			{
                		if (PheTile[iph] == 0 && Phe[iph]>0.5)
				{
					harray[0]->Fill(PheTime[iph]/1000.+offset1);
				}
                        	if (PheTile[iph] == 1 && Phe[iph]>0.5)
				{
					harray[1]->Fill(PheTime[iph]/1000.+offset1);
				}
                                else if (PheTile[iph] == 2 && Phe[iph]>0.5)
				{
                        		timeh3->Fill(PheTime[iph]/1000.+offset2);
                        		// 60 microseconds bunches
                        		timeh1->Fill(PheTime[iph]/1000.);
					harray[2]->Fill(PheTime[iph]/1000.+offset1);
				}
         	                else if (PheTile[iph] == 3 && Phe[iph]>0.5)
				{
					harray[3]->Fill(PheTime[iph]/1000.+offset1);
				}
	 			timeh2->Fill(PheTime[iph]/1000.+offset1);
				for ( int j=0; j<115;  j++)
				{
                          		Float_t newtime=PheTime[iph]+offset1*1000. +j*16.0;
                          		newtime=newtime/1000.;
                          		Float_t cont =response[j]*Phe[iph]*effi;
                          		tcglob->Fill(newtime,cont);
                          		tc->Fill(newtime,cont);
				}
			}
			for (int iphNCap=0; iphNCap<NPheHitsNCap; iphNCap++)
			{
                		if (PheTileNCap[iphNCap] == 0 && PheNCap[iphNCap]>0.5)
				{
					harrayNCap[0]->Fill(PheTimeNCap[iphNCap]/1000.+offset2);
				}
                        	if (PheTileNCap[iphNCap] == 1 && PheNCap[iphNCap]>0.5)
				{
					harrayNCap[1]->Fill(PheTimeNCap[iphNCap]/1000.+offset2);
				}
                                else if (PheTileNCap[iphNCap] == 2 && PheNCap[iphNCap]>0.5)
				{
                        		timeh3NCap->Fill(PheTimeNCap[iphNCap]/1000.+offset2);
                        		// 60 microseconds bunches
                        		timeh1NCap->Fill(PheTimeNCap[iphNCap]/1000.);
					harrayNCap[2]->Fill(PheTimeNCap[iphNCap]/1000.+offset2);
				}
         	                else if (PheTileNCap[iphNCap] == 3 && PheNCap[iphNCap]>0.5)
				{
					harrayNCap[3]->Fill(PheTimeNCap[iphNCap]/1000.+offset2);
				}
	 			timeh2NCap->Fill(PheTimeNCap[iphNCap]/1000.+offset1);
				for ( int j=0; j<115;  j++)
				{
                          		Float_t newtime=PheTimeNCap[iphNCap]+offset1*1000. +j*16.0;
                          		newtime=newtime/1000.;
                          		Float_t cont =response[j]*PheNCap[iphNCap]*effi;
                          		tcglobNCap->Fill(newtime,cont);
                          		tcNCap->Fill(newtime,cont);
				}
			}
		}
		
	}
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
	
	std::cout << "Total Neutron Interactions: " << total_neut_int << std::endl;

	std::cout << "Total Inelastic Events: " << sum_303 << "  " << (float(sum_303)/total_neut_int) * 100 << " %" << std::endl; 
	std::cout << "Total Neutron Capture Events: " << sum_306 << "  " << (float(sum_306)/total_neut_int) * 100 << " %"<< std::endl; 
	std::cout << "Total Inelastic + Neutron Capture Events: " << multi_sum << "  " << (float(multi_sum)/total_neut_int) * 100 << " %"<< std::endl; 
	
	

	TF1 *func = new TF1("fit",fitf,100,800,3);	

	std::cout << "\ntimeh2 Fit:" << std::endl;
	timeh2->Fit("fit","R");

	std::cout << "\ntcglob Fit:" << std::endl;
	tcglob->Fit("fit","R");
	
	//std::cout << "\ntimeine306 Fit:\n" << std::endl;
	//harray[1]->Fit("fit","R");

	TCanvas *c1 = new TCanvas();
        timeh1->Draw();
        c1->SaveAs("images_jul24/timeh1_test.png");
	TCanvas *c2 = new TCanvas();
        timeh2->Draw();
        c2->SaveAs("images_jul24/timeh2_test.png");
	TCanvas *c3 = new TCanvas();
        timeh3->Draw();
        c3->SaveAs("images_jul24/timeh3_test.png");
	TCanvas *c4 = new TCanvas();
        tcglob->Draw();
        c4->SaveAs("images_jul24/tcglob_test.png");
	TCanvas *c5 = new TCanvas();
        tc->Draw();
        c5->SaveAs("images_jul24/tc_test.png");

	for(int i = 0; i<4; i++)
	{
		//TString print_name = Form("timeine%d",int_array[i]);
		//std::cout << "\n" << print_name<< " Fit:" << std::endl;
        	//harray[i]->Fit("fit","R");
	
		//hs->Add(harray[i]);
		//timehstack->Add(harray[i]);

		TCanvas *c = new TCanvas();
        	harray[i]->Draw();
        	TString filename = Form("images_jul24/timetile%d_test.png",i);
		c->SaveAs(filename);	
		
		TString tileout = Form("timetile%d",i);
		std::cout << "\n" << tileout << " Fit:" << std::endl;
        	harray[i]->Fit("fit","R");
	}

	TCanvas *c1NCap = new TCanvas();
        timeh1NCap->Draw();
        c1NCap->SaveAs("images_jul24/timeh1NCap_test.png");
	TCanvas *c2NCap = new TCanvas();
        timeh2NCap->Draw();
        c2NCap->SaveAs("images_jul24/timeh2NCap_test.png");
	TCanvas *c3NCap = new TCanvas();
        timeh3NCap->Draw();
        c3NCap->SaveAs("images_jul24/timeh3NCap_test.png");
	TCanvas *c4NCap = new TCanvas();
        tcglobNCap->Draw();
        c4NCap->SaveAs("images_jul24/tcglobNCap_test.png");
	TCanvas *c5NCap = new TCanvas();
        tcNCap->Draw();
        c5NCap->SaveAs("images_jul24/tcNCap_test.png");

	for(int i = 0; i<4; i++)
	{
		//TString print_name = Form("timeine%d",int_array[i]);
		//std::cout << "\n" << print_name<< " Fit:" << std::endl;
        	//harray[i]->Fit("fit","R");
	
		//hs->Add(harray[i]);
		//timehstack->Add(harray[i]);

		TCanvas *c = new TCanvas();
        	harrayNCap[i]->Draw();
        	TString filename = Form("images_jul24/timetile%dNCap_test.png",i);
		c->SaveAs(filename);	
	}

	
	TCanvas *c6 = new TCanvas();
        posinex->Draw();
        c6->SaveAs("images_jul24/posinex_test.png");
	TCanvas *c7 = new TCanvas();
        posiney->Draw();
        c7->SaveAs("images_jul24/posiney_test.png");
	TCanvas *c8 = new TCanvas();
        posinez->Draw();
        c8->SaveAs("images_jul24/posinez_test.png");
	
	TCanvas *c9 = new TCanvas();
        posinex303->Draw();
        c9->SaveAs("images_jul24/posinex303_test.png");
	TCanvas *c10 = new TCanvas();
        posiney303->Draw();
        c10->SaveAs("images_jul24/posiney303_test.png");
	TCanvas *c11 = new TCanvas();
        posinez303->Draw();
        c11->SaveAs("images_jul24/posinez303_test.png");

	TCanvas *c12 = new TCanvas();
        posinex306->Draw();
        c12->SaveAs("images_jul24/posinex306_test.png");
	TCanvas *c13 = new TCanvas();
        posiney306->Draw();
        c13->SaveAs("images_jul24/posiney306_test.png");
	TCanvas *c14 = new TCanvas();
        posinez306->Draw();
        c14->SaveAs("images_jul24/posinez306_test.png");
	
	TCanvas *c15 = new TCanvas();
        mominex->Draw();
        c15->SaveAs("images_jul24/mominex_test.png");
	TCanvas *c16 = new TCanvas();
        mominey->Draw();
        c16->SaveAs("images_jul24/mominey_test.png");
	TCanvas *c17 = new TCanvas();
        mominez->Draw();
        c17->SaveAs("images_jul24/mominez_test.png");
	TCanvas *c18 = new TCanvas();
        toteine->Draw();
        c18->SaveAs("images_jul24/toteine_test.png");
	TCanvas *c19 = new TCanvas();
        kineine->Draw();
        c19->SaveAs("images_jul24/kineine_test.png");
	
	TCanvas *c20 = new TCanvas();
        mominex303->Draw();
        c20->SaveAs("images_jul24/mominex303_test.png");
	TCanvas *c21 = new TCanvas();
        mominey303->Draw();
        c21->SaveAs("images_jul24/mominey303_test.png");
	TCanvas *c22 = new TCanvas();
        mominez303->Draw();
        c22->SaveAs("images_jul24/mominez303_test.png");
	TCanvas *c23 = new TCanvas();
        toteine303->Draw();
        c23->SaveAs("images_jul24/toteine303_test.png");
	TCanvas *c24 = new TCanvas();
        kineine303->Draw();
        c24->SaveAs("images_jul24/kineine303_test.png");
	
	TCanvas *c25 = new TCanvas();
        mominex306->Draw();
        c25->SaveAs("images_jul24/mominex306_test.png");
	TCanvas *c26 = new TCanvas();
        mominey306->Draw();
        c26->SaveAs("images_jul24/mominey306_test.png");
	TCanvas *c27 = new TCanvas();
        mominez306->Draw();
        c27->SaveAs("images_jul24/mominez306_test.png");
	TCanvas *c28 = new TCanvas();
        toteine306->Draw();
        c28->SaveAs("images_jul24/toteine306_test.png");
	TCanvas *c29 = new TCanvas();
        kineine306->Draw();
        c29->SaveAs("images_jul24/kineine306_test.png");
	
	TCanvas *c30 = new TCanvas();
        posinexgamma->Draw();
        c30->SaveAs("images_jul24/posinexgamma_test.png");
	TCanvas *c31 = new TCanvas();
        posineygamma->Draw();
        c31->SaveAs("images_jul24/posineygamma_test.png");
	TCanvas *c32 = new TCanvas();
        posinezgamma->Draw();
        c32->SaveAs("images_jul24/posinezgamma_test.png");
	TCanvas *c33 = new TCanvas();
        mominexgamma->Draw();
        c33->SaveAs("images_jul24/mominexgamma_test.png");
	TCanvas *c34 = new TCanvas();
        momineygamma->Draw();
        c34->SaveAs("images_jul24/momineygamma_test.png");
	TCanvas *c35 = new TCanvas();
        mominezgamma->Draw();
        c35->SaveAs("images_jul24/mominezgamma_test.png");
	TCanvas *c36 = new TCanvas();
        toteinegamma->Draw();
        c36->SaveAs("images_jul24/toteinegamma_test.png");
	TCanvas *c37 = new TCanvas();
        kineinegamma->Draw();
        c37->SaveAs("images_jul24/kineinegamma_test.png");
}



