//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: QuatFromRotJ.cpp
//
// MATLAB Coder version            : 2.8
// C/C++ source code generated on  : 14-Aug-2015 13:34:16
//

// Include Files
#include "rt_nonfinite.h"
#include "SLAM.h"
#include "QuatFromRotJ.h"
#include "SLAM_updIT.h"
#include "SLAM_rtwutil.h"
#include <stdio.h>

// Function Definitions

//
// THIS IS OK, It is according to the NASA memo found
//  https://claraty.jpl.nasa.gov/man/software/development/conventions/standards_docs/unadopted/JPL_Quaternions_Breckenridge.pdf
// QUATFROMROTJ Get equivalent quaternion of the rotation matrix R
//    Returns a quaternion in JPL notation
//  The implementation is copied from qGetQ(R), but we are careful about the
//  ordering of the output vector
// Arguments    : const double R[9]
//                double b_Q[4]
// Return Type  : void
//
void QuatFromRotJ(const double R[9], double b_Q[4])
{
  double b_T;
  double mtmp;
  double b_mtmp;
  double x;
  double pivot[4];
  double c_mtmp;
  double d_mtmp;
  double d0;
  int ix;
  int idx;
  signed char ii_data[4];
  boolean_T exitg1;
  boolean_T guard1 = false;
  int loop_ub;
  int i0;
  signed char i_data[4];
  signed char index_data[4];

  //  [r,c] = size( R );
  //  if( r ~= 3 || c ~= 3 )
  //      error( 'R must be a 3x3 matrix\n\r' );
  //  end
  b_T = (R[0] + R[4]) + R[8];
  mtmp = (1.0 + 2.0 * R[0]) - b_T;
  if (mtmp >= 2.2204460492503131E-16) {
    b_mtmp = mtmp;
  } else {
    b_mtmp = 2.2204460492503131E-16;
  }

  x = sqrt(b_mtmp);
  pivot[0] = x / 2.0;
  mtmp = (1.0 + 2.0 * R[4]) - b_T;
  if (mtmp >= 2.2204460492503131E-16) {
    c_mtmp = mtmp;
  } else {
    c_mtmp = 2.2204460492503131E-16;
  }

  pivot[1] = sqrt(c_mtmp) / 2.0;
  mtmp = (1.0 + 2.0 * R[8]) - b_T;
  if (mtmp >= 2.2204460492503131E-16) {
    d_mtmp = mtmp;
  } else {
    d_mtmp = 2.2204460492503131E-16;
  }

  pivot[2] = sqrt(d_mtmp) / 2.0;
  if (1.0 + b_T >= 2.2204460492503131E-16) {
    d0 = 1.0 + b_T;
  } else {
    d0 = 2.2204460492503131E-16;
  }

  pivot[3] = sqrt(d0) / 2.0;
  mtmp = x / 2.0;
  for (ix = 1; ix + 1 < 5; ix++) {
    if (pivot[ix] > mtmp) {
      mtmp = pivot[ix];
    }
  }

  idx = 0;
  ix = 1;
  exitg1 = false;
  while ((!exitg1) && (ix < 5)) {
    guard1 = false;
    if (pivot[ix - 1] == mtmp) {
      idx++;
      ii_data[idx - 1] = (signed char)ix;
      if (idx >= 4) {
        exitg1 = true;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      ix++;
    }
  }

  if (1 > idx) {
    loop_ub = 0;
  } else {
    loop_ub = idx;
  }

  for (i0 = 0; i0 < loop_ub; i0++) {
    i_data[i0] = ii_data[i0];
  }

  if (1 > idx) {
    ix = 0;
  } else {
    ix = idx;
  }

  for (i0 = 0; i0 < ix; i0++) {
    index_data[i0] = i_data[i0];
  }

  for (ix = 0; ix < loop_ub; ix++) {
    index_data[ix] = (signed char)rt_roundd_snf((double)index_data[ix]);
  }

  if (index_data[0] == 1) {
    x = sqrt((1.0 + 2.0 * R[0]) - b_T);
    mtmp = x / 2.0;
    b_Q[0] = x / 2.0;
    b_Q[1] = (R[3] + R[1]) / (4.0 * mtmp);
    b_Q[2] = (R[6] + R[2]) / (4.0 * mtmp);
    b_Q[3] = (R[7] - R[5]) / (4.0 * mtmp);
  } else if (index_data[0] == 2) {
    x = sqrt((1.0 + 2.0 * R[4]) - b_T);
    mtmp = x / 2.0;
    b_Q[1] = x / 2.0;
    b_Q[0] = (R[3] + R[1]) / (4.0 * mtmp);
    b_Q[2] = (R[7] + R[5]) / (4.0 * mtmp);
    b_Q[3] = (R[2] - R[6]) / (4.0 * mtmp);
  } else if (index_data[0] == 3) {
    x = sqrt((1.0 + 2.0 * R[8]) - b_T);
    mtmp = x / 2.0;
    b_Q[2] = x / 2.0;
    b_Q[0] = (R[6] + R[2]) / (4.0 * mtmp);
    b_Q[1] = (R[7] + R[5]) / (4.0 * mtmp);
    b_Q[3] = (R[3] - R[1]) / (4.0 * mtmp);
  } else {
    x = sqrt(1.0 + b_T);
    mtmp = x / 2.0;
    b_Q[3] = x / 2.0;
    b_Q[0] = (R[7] - R[5]) / (4.0 * mtmp);
    b_Q[1] = (R[2] - R[6]) / (4.0 * mtmp);
    b_Q[2] = (R[3] - R[1]) / (4.0 * mtmp);
  }
}

//
// THIS IS OK, It is according to the NASA memo found
//  https://claraty.jpl.nasa.gov/man/software/development/conventions/standards_docs/unadopted/JPL_Quaternions_Breckenridge.pdf
// QUATFROMROTJ Get equivalent quaternion of the rotation matrix R
//    Returns a quaternion in JPL notation
//  The implementation is copied from qGetQ(R), but we are careful about the
//  ordering of the output vector
// Arguments    : double b_Q[4]
// Return Type  : void
//
void b_QuatFromRotJ(double b_Q[4])
{
  int idx;
  signed char ii_data[4];
  int ii;
  boolean_T exitg1;
  boolean_T guard1 = false;
  static const boolean_T x[4] = { false, false, false, true };

  int loop_ub;
  int i11;
  signed char i_data[4];
  signed char index_data[4];

  //  [r,c] = size( R );
  //  if( r ~= 3 || c ~= 3 )
  //      error( 'R must be a 3x3 matrix\n\r' );
  //  end
  idx = 0;
  ii = 1;
  exitg1 = false;
  while ((!exitg1) && (ii < 5)) {
    guard1 = false;
    if (x[ii - 1]) {
      idx++;
      ii_data[idx - 1] = (signed char)ii;
      if (idx >= 4) {
        exitg1 = true;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      ii++;
    }
  }

  if (1 > idx) {
    loop_ub = 0;
  } else {
    loop_ub = idx;
  }

  for (i11 = 0; i11 < loop_ub; i11++) {
    i_data[i11] = ii_data[i11];
  }

  if (1 > idx) {
    ii = 0;
  } else {
    ii = idx;
  }

  for (i11 = 0; i11 < ii; i11++) {
    index_data[i11] = i_data[i11];
  }

  for (ii = 0; ii < loop_ub; ii++) {
    index_data[ii] = (signed char)rt_roundd_snf((double)index_data[ii]);
  }

  if (index_data[0] == 1) {
    b_Q[0] = 0.0;
    b_Q[1] = rtNaN;
    b_Q[2] = rtNaN;
    b_Q[3] = rtNaN;
  } else if (index_data[0] == 2) {
    b_Q[1] = 0.0;
    b_Q[0] = rtNaN;
    b_Q[2] = rtNaN;
    b_Q[3] = rtNaN;
  } else if (index_data[0] == 3) {
    b_Q[2] = 0.0;
    b_Q[0] = rtNaN;
    b_Q[1] = rtNaN;
    b_Q[3] = rtNaN;
  } else {
    b_Q[3] = 1.0;
    b_Q[0] = 0.0;
    b_Q[1] = 0.0;
    b_Q[2] = 0.0;
  }
}

//
// File trailer for QuatFromRotJ.cpp
//
// [EOF]
//