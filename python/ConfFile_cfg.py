import FWCore.ParameterSet.Config as cms
import flashgg.Taggers.flashggTags_cff as flashggTags

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:/afs/cern.ch/work/r/rateixei/work/DiHiggs/Jets80X/CMSSW_8_0_8_patch1/src/flashgg/myMicroAODOutputFile.root'
    )
)

process.demo = cms.EDAnalyzer('MyFlashggDumper')

process.load("flashgg.Taggers.flashggTags_cff")
process.demo.inputTagJets = flashggTags.UnpackedJetCollectionVInputTag
process.p = cms.Path(flashggTags.flashggUnpackedJets*process.demo)
