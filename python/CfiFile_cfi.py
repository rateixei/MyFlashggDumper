import FWCore.ParameterSet.Config as cms
import flashgg.Taggers.flashggTags_cff as flashggTags

demo = cms.EDAnalyzer('MyFlashggDumper',

inputTagJets = flashggTags.UnpackedJetCollectionVInputTag

)
