void sim(Int_t nev=1) {
  AliSimulation simulator;
  if (gSystem->Getenv("EVENT"))
   nev = atoi(gSystem->Getenv("EVENT")) ;   
  simulator.SetWriteRawData("ALL","raw.root",kTRUE);

  simulator.SetDefaultStorage("local://$ALICE_ROOT/OCDB");
  simulator.SetSpecificStorage("GRP/GRP/Data",
			       Form("local://%s",gSystem->pwd()));
  simulator.SetSpecificStorage("VZERO/Calib/Data",
			       "local://$ALICE_ROOT/OCDB/VZERO/PbPb");
  simulator.SetRunQA("ALL:ALL") ; 
  simulator.SetQARefDefaultStorage("local://$ALICE_ROOT/QAref") ;
  
  for (Int_t det = 0 ; det < AliQA::kNDET ; det++) {
    simulator.SetQACycles(det, nev+1) ;
  }
  TStopwatch timer;
  timer.Start();
  simulator.Run(nev);
  timer.Stop();
  timer.Print();
}
