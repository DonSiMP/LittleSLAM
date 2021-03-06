/****************************************************************************
 * LittleSLAM: 2D-Laser SLAM for educational use
 * Copyright (C) 2017-2018 Masahiro Tomono
 * Copyright (C) 2018 Future Robotics Technology Center (fuRo),
 *                    Chiba Institute of Technology.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * @file LoopDetectorSS.h
 * @author Masahiro Tomono
 ****************************************************************************/

#ifndef LOOP_DETECTOR_SS_H_
#define LOOP_DETECTOR_SS_H_

#include "LoopDetector.h"
#include "PointCloudMapLP.h"
#include "DataAssociator.h"
#include "PoseEstimatorICP.h"
#include "PoseFuser.h"


////////////

class LoopDetectorSS : public LoopDetector
{
private:
  double radius;                               // TυΌa[m]i»έΚuΖΔK_Μ£θlj
  double atdthre;                              // έΟs£Μ·Μθl[m]
  double scthre;                               // ICPXRAΜθl

  PointCloudMapLP *pcmap;                      // _Qn}
  CostFunction *cfunc;                         // RXgΦ(ICPΖΝΚΙg€)
  PoseEstimatorICP *estim;                     // {bgΚuθν(ICP)
  DataAssociator *dass;                        // f[^ΞΓ―ν
  PoseFuser *pfu;                              // ZTZν

public:
  LoopDetectorSS() : radius(4), atdthre(10), scthre(0.2) {
  }

  ~LoopDetectorSS() {
  }

/////////

  void setPoseEstimator(PoseEstimatorICP *p) {
    estim = p;
  }

  void setPoseFuser(PoseFuser *p) {
    pfu = p;
  }

  void setDataAssociator(DataAssociator *d) {
    dass = d;
  }

  void setCostFunction(CostFunction *f) {
    cfunc = f;
  }

  void setPointCloudMap(PointCloudMapLP *p) {
    pcmap = p;
  }

//////////

  virtual bool detectLoop(Scan2D *curScan, Pose2D &curPose, int cnt);
  void makeLoopArc(LoopInfo &info);
  bool estimateRevisitPose(const Scan2D *curScan, const std::vector<LPoint2D> &refLps, const Pose2D &initPose, Pose2D &revisitPose);

};

#endif
