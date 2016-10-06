// -*- C++ -*-
//
// Package:    flashgg/MyFlashggDumper
// Class:      MyFlashggDumper
// 
/**\class MyFlashggDumper MyFlashggDumper.cc flashgg/MyFlashggDumper/plugins/MyFlashggDumper.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Rafael Teixeira De Lima
//         Created:  Thu, 06 Oct 2016 16:08:01 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

//FLASHgg files
#include "flashgg/DataFormats/interface/DiPhotonCandidate.h"
#include "flashgg/DataFormats/interface/SinglePhotonView.h"
#include "flashgg/DataFormats/interface/Photon.h"
#include "flashgg/DataFormats/interface/Jet.h"

class MyFlashggDumper : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit MyFlashggDumper(const edm::ParameterSet&);
      typedef std::vector<edm::Handle<edm::View<flashgg::Jet> > > JetCollectionVector;

      ~MyFlashggDumper();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
   std::vector<edm::InputTag> inputTagJets_;
   std::vector<edm::EDGetTokenT<edm::View<flashgg::Jet> > > tokenJets_;


};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
MyFlashggDumper::MyFlashggDumper(const edm::ParameterSet& iConfig) : 
inputTagJets_( iConfig.getParameter<std::vector<edm::InputTag> >( "inputTagJets" ) )
{
   //now do what ever initialization is needed
   usesResource("TFileService");

    for (unsigned i = 0 ; i < inputTagJets_.size() ; i++) {
        auto token = consumes<edm::View<flashgg::Jet> >(inputTagJets_[i]);
        tokenJets_.push_back(token);
    }

}


MyFlashggDumper::~MyFlashggDumper()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
MyFlashggDumper::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   JetCollectionVector theJetsCols( inputTagJets_.size() );
   for( size_t j = 0; j < inputTagJets_.size(); ++j ) {
      iEvent.getByToken( tokenJets_[j], theJetsCols[j] );
   }

   std::cout << "--- New Event! ---" << std::endl;

   std::cout << "Number of jet collections!!!! " << theJetsCols.size() << std::endl;

   if( theJetsCols.size() < 1 ) return;

   std::cout << "Number of jets in 0th jet collection!!!! " << theJetsCols[0]->size() << std::endl;

   if( theJetsCols[0]->size() < 1) return;

   std::cout << "Pt of 0th jet in 0th jet col: " << theJetsCols[0]->ptrAt(0)->pt() << std::endl;
   //user floats
   std::cout << "0th jet user floats: " << std::endl;
   size_t nfloats = theJetsCols[0]->ptrAt(0)->userFloatNames().size();
   for ( size_t nf = 0; nf < nfloats; nf++) {
      std::string thisUserFloatName = theJetsCols[0]->ptrAt(0)->userFloatNames()[nf];
      std::cout << "\t User float: " << thisUserFloatName << "  -  value: " << theJetsCols[0]->ptrAt(0)->userFloat(thisUserFloatName) << std::endl;

   }

   std::cout << "--- End Event! ---" << std::endl;

}


// ------------ method called once each job just before starting event loop  ------------
void 
MyFlashggDumper::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MyFlashggDumper::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
MyFlashggDumper::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(MyFlashggDumper);
