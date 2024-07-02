#define vbox_cxx
#include "vbox.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void vbox::Loop()
{
//   In a ROOT session, you can do:
//      root> .L hits_code.C
//      root> hits_code t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fheader == 0) return;
   TRandom *myran       = new TRandom();
   Double_t rr=0.0, rr2=0.0, offset1=0.0, offset2=0.0;
   Long64_t nentries = fheader->GetEntriesFast();
   int nmaxima=0;
   ofstream myfile;
   int myevent=-1;
   int nnmax=100;
   Long64_t nbytes = 0, nb = 0, nbh=0;
   Double_t response[115];
   Double_t thr1=10.0; //total phe on 1 tile to get above threshold
   //  Double_t thr2=14.5*10.;
   Double_t thr2=14.5*5.; // 5 phe
   Double_t effi=0.3; // Efficiency. Factor 0.10 already accounted in sim. 
   TFile* rfile= TFile::Open("sample.root");
   //            TCanvas *c2 =new TCanvas("c2","c2",1500,1500);

TCanvas* h = nullptr;
rfile->GetObject("cpers_s",h);
 TH1D *avg = (TH1D*)h->GetPrimitive("haverage_s_Ch0");
	 for (int i=0; i<115;  i++){
	   response[i]=avg->GetBinContent(i+388);
	 }
	   Int_t imax=avg->GetMaximumBin();
	   cout << imax << " max " << response[imax-388] << endl;
   
   rfile->Close();
   int ngoodevts=0;
   //   c2->cd();
   //   			  myfile.open("dump.dat");

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fhits->GetEntry(jentry);   nbytes += nb;
      nbh = fheader->GetEntry(jentry); //  nbytes += nb;
      if (tc != nullptr ) {delete tc;}

	  tc= new TH1F("tc","convoluted",75000,0.,1200.);
			  tc->GetXaxis()->SetRange(1,75000);  
	  
	  if (TotPhe[2]*effi>thr1) {
		rr2=myran->Rndm();
		rr2=rr2*5;
		rr2=Int_t(rr2)*80.0; //-280.0;
		rr=myran->Rndm();
		offset2=rr*60.0+rr2;
		offset1=offset2-280.0;
		for (int iph=0; iph<NPheHits; iph++) {
		  if (PheTile[iph] == 2 && Phe[iph]>0.5) {
			timeh3->Fill(PheTime[iph]/1000.+offset2);
			// 60 microseconds bunches
			timeh1->Fill(PheTime[iph]/1000.);}
			timeh2->Fill(PheTime[iph]/1000.+offset1);
			if (EveNum==myevent){ cout << Phe[iph] << " filling " << PheTime[iph]<<" moved to " << PheTime[iph]+offset1*1000.<< " offset1 "<< offset1<<endl;}
			for ( int i=0; i<115;  i++){
			  Float_t newtime=PheTime[iph]+offset1*1000. +i*16.0;
			  newtime=newtime/1000.;
			  Float_t cont =response[i]*Phe[iph]*effi;
			  tcglob->Fill(newtime,cont);
			  tc->Fill(newtime,cont);
			if (EveNum==myevent){ cout << i << " newtime " << newtime <<" content" << cont << endl;}
			}
		} //end loop on phe hits to generate  non-convoluted analisys
		  // and convoluted waveform. now find peaks
  		nmaxima=0;
		int dum=tc->GetMaximumBin();
		//		myfile << EveNum <<" event, totph " << TotPhe[2] <<  " all max " << tc->GetBinContent(dum) << " time  " << dum*16.0<<endl;
		if ( tc->GetBinContent(dum) > thr2) {
			ngoodevts++;
			//		  cout << ngoodevts <<" good event " << EveNum<<endl;

		  //			cout << tc->GetBinContent(dum) << " above " << thr2 <<" thresh " <<ngoodevts<<endl;
		  
			if (EveNum== myevent ) {
			  myfile.open("dump.dat");
			  for (int jj=1; jj<75000; jj++){
				myfile<< jj<< " " << tc->GetBinContent(jj) <<endl;}
			  myfile.close();} 
			int jmin=1;
			Float_t mymax=0.0;
			Float_t mymax_prev=0.0;
			int k=0;
			Float_t val=0.;
			while (jmin < 74000 ){
			  tc->GetXaxis()->SetRange(jmin,75000);  
			  if (EveNum== myevent ) {cout << k <<" k, jmin " << jmin << endl;}
			  k=-1;
			  for (int jj=jmin; jj<75000; jj++){
				val=tc->GetBinContent(jj);
				if (EveNum== myevent ){cout<<jj<< " looking " << val<<endl;}
				if (val > thr2) {
				  k=jj;
				  break;	
				}
			  }
			  if (EveNum== myevent ) {cout << k <<" kfound " << val << endl;}
			  if (k > 0) {
				Int_t kmax=k;
				Int_t kprev=kmax;
				mymax=tc->GetBinContent(k);
				while (mymax_prev < mymax && k<74900){
			 // step by 100 channels, find max in each step,
			 // stop when decreasing
				  mymax_prev = mymax;
				  kprev=kmax;
				  tc->GetXaxis()->SetRange(k+1,k+100);  
				  kmax= tc->GetMaximumBin();
				  mymax=tc->GetBinContent(kmax);
				  k=k+100;
				  if (EveNum== myevent )	{
					cout << mymax_prev <<" maxima  " << mymax << endl;
					cout << kprev <<" kprev " << k << endl;
					cout << kmax <<" kmax, knew " << k << endl;}
				}
		   // keep this one
			  //			  cout << kprev << " found " <<endl;
				Double_t thistime=kprev*16.E-03;
				nmaxima++;
				if (nmaxima > nnmax) {break;}
			  //			  cout << thistime << " filling " <<nmaxima << " " << ngoodevts<< endl;
				tall->Fill(thistime);
				tcompact->Fill(thistime);
		   // set to start next window: see when it rises again
				mymax_prev=mymax;
			  
				while (mymax_prev >= mymax && k<74900){
				  mymax_prev=mymax;
				  tc->GetXaxis()->SetRange(k+1,k+100);
				  kmax= tc->GetMaximumBin();
				  mymax=tc->GetBinContent(kmax);
				  k=k+100;
				  if (EveNum== myevent ) {cout << k << " newk found " << mymax<< endl;}
				}
				jmin=k-99;
				if (EveNum== myevent )	{cout << jmin << " jmin found " <<endl;}
			  }
			  else {jmin=75000;}}
		} //end if on at least 1 bin above threshold
	  } // end if on totphe
	  if (nmaxima > nnmax ) {cout <<EveNum<<endl; break;}
	  //	  if (ngoodevts >1000) break;
   }//end loop on entries
   cout << "number of events with signal above thr " << ngoodevts <<endl;
      // if (Cut(ientry) < 0) continue;
   //   myfile.close();

TCanvas *c2 =new TCanvas("c2","c2",1500,1500);
 c2->cd();
 timeh2->Draw();
 c2->Print("vbox_timeh2.png");
 timeh3->Draw();
 c2->Print("vbox_timeh3.png");
 tcompact->Draw();
 c2->Print("vbox_tconv.png");
 
}


