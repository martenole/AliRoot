#ifndef ALIMUONTRACKHITPATTERN_H
#define ALIMUONTRACKHITPATTERN_H
/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

/*$Id$*/

/// \ingroup rec
/// \class AliMUONTrackHitPattern
/// \brief Class for the MUON track hit pattern
///
//  Author: Diego Stocco

#include <TObject.h>
//#include <TObjArray.h>

class AliMUONVTrackStore;
class AliMUONVTriggerStore;
class AliMUONVTriggerTrackStore;
class AliMUONTrackParam;
class AliMUONGeometryTransformer;
class AliMUONVDigitStore;
class AliMUONTriggerTrack;
class AliMUONTrack;
class AliMUONRecoParam;
class AliMUONTriggerUtilities;
class AliMpPad;
class TVector3;
class TArrayI;

class AliMUONTrackHitPattern : public TObject 
{
public:

  AliMUONTrackHitPattern(const AliMUONRecoParam* recoParam,
                         const AliMUONGeometryTransformer& transformer,
                         const AliMUONVDigitStore& digitStore,
                         const AliMUONTriggerUtilities* triggerUtilities);
  virtual ~AliMUONTrackHitPattern(); // Destructor

  void ExecuteValidation(const AliMUONVTrackStore& trackStore,
			 const AliMUONVTriggerTrackStore& triggerTrackStore,
			 const AliMUONVTriggerStore& triggerStore) const;
  
  AliMUONTriggerTrack* MatchTriggerTrack(AliMUONTrack* track,
					 AliMUONTrackParam& trackParam,
					 const AliMUONVTriggerTrackStore& triggerTrackStore,
					 const AliMUONVTriggerStore& triggerStore) const;
  
  UInt_t GetHitPattern(const AliMUONTrackParam& trackParam, Bool_t isTriggerTrack) const;
  
  UInt_t GetHitPattern(const AliMUONTriggerTrack* matchedTriggerTrack) const; // obsolete
  UInt_t GetHitPattern(AliMUONTrackParam* trackParam) const; // obsolete

protected:
  void ApplyMCSCorrections(AliMUONTrackParam& trackParam) const;
  
  Int_t GetTrackParamAtChamber(const AliMUONTrackParam& inputTrackParam, Int_t chamber,
                               TObjArray& trackParamList, TArrayI& foundDetElemId, TObjArray& padsFromPos) const;
  
  Bool_t FindMatchingPads(const AliMUONTrackParam* trackParam,
                          TArrayI& matchedDetElemId, TObjArray& pads,
                          const AliMUONVDigitStore& digitStore, Bool_t isTriggerTrack) const;
  
  Bool_t PosInDetElemIdLocal(TVector3& localCoor, const TVector3& globalPoint1, const TVector3& globalPoint2, Int_t detElemId) const;
  
  /// Return reco parameters
  const AliMUONRecoParam* GetRecoParam() const { return fkRecoParam; }
  
  // THE FOLLOWING METHODS ARE OBSOLETE
  
  // Methods for hit pattern from tracker track
  void FindPadMatchingTrack(const AliMUONTrackParam& trackParam,
                            Bool_t isMatch[2], Int_t iChamber) const;

  Float_t MinDistanceFromPad(Float_t xPad, Float_t yPad, Float_t zPad,
                             Float_t dpx, Float_t dpy, 
                             const AliMUONTrackParam& trackParam) const;

  // Methods for hit pattern from matched trigger track
  Bool_t PerformTrigTrackMatch(UInt_t &pattern, const AliMUONTriggerTrack* matchedTrigTrack) const; // obsolete
  
  Bool_t FindPadMatchingTrig(const TVector3& vec11, const TVector3& vec21, Int_t matchedDetElemId[2], TObjArray& matchedPads) const; // obsolete
  
  Float_t PadMatchTrack(const AliMpPad& pad, const TVector3& trackPosAtPad) const; // obsolete
  
  Int_t DetElemIdFromPos(Float_t x, Float_t y, Int_t chamber, Int_t foundDetElemId[2]) const; // obsolete
  
  Bool_t PadsFromPos(const TVector3& vec11, const TVector3& vec21, Int_t detElemId, TObjArray& pads) const; // obsolete
  
  
  Bool_t IsCloseToAccEdge(TObjArray& pads, Int_t detElemId, Float_t coor[2]) const; // obsolete
  
  Bool_t IsMasked(const AliMpPad& pad, Int_t detElemId, Int_t cathode, const TVector3& vec11, const TVector3& vec21) const; // obsolete
  
private:
  /// Not implemented
  AliMUONTrackHitPattern(const AliMUONTrackHitPattern& rhs);
  /// Not implemented
  AliMUONTrackHitPattern& operator = (const AliMUONTrackHitPattern& rhs);

  const AliMUONRecoParam* fkRecoParam; //!<! pointer to reco parameters
  const AliMUONGeometryTransformer& fkTransformer; //!<! geometry transformer
  const AliMUONVDigitStore& fkDigitStore; //!<! digitStore
  const AliMUONTriggerUtilities* fkTriggerUtilities; //!<! trigger utilities for mapping

  const Float_t fkMaxDistance; //!<! Maximum distance for reference // obsolete
  
  ClassDef(AliMUONTrackHitPattern, 0) // MUON track hit pattern
};

#endif
