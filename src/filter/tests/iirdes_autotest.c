/*
 * Copyright (c) 2007 - 2020 Joseph Gaeddert
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

// References
//  [Ziemer:1998] Ziemer, Tranter, Fannin, "Signals & Systems,
//      Continuous and Discrete," 4th ed., Prentice Hall, Upper

#include "autotest/autotest.h"
#include "liquid.internal.h"

// design 2nd-order butterworth filter (design comes from [Ziemer:1998],
// Example 9-7, pp. 440--442)
void autotest_iirdes_butter_2()
{
    // initialize variables
    unsigned int order = 2; // filter order
    float fc = 0.25f;       // normalized cutoff frequency
    float f0 = 0.0f;        // center frequency (ignored for low-pass filter)
    float Ap = 1.0f;        // pass-band ripple (ignored for Butterworth)
    float As = 40.0f;       // stop-band attenuation (ignored for Butterworth)
    float tol = 1e-6f;      // error tolerance

    // initialize pre-determined coefficient array
    // for 2^nd-order low-pass Butterworth filter
    // with cutoff frequency 0.25
    float a_test[3] = {
        1.0f,
        0.0f,
        0.171572875253810f};
    float b_test[3] = {
        0.292893218813452f,
        0.585786437626905f,
        0.292893218813452f};

    // output coefficients
    float a[3];
    float b[3];

    // design butterworth filter
    liquid_iirdes(LIQUID_IIRDES_BUTTER,
                  LIQUID_IIRDES_LOWPASS,
                  LIQUID_IIRDES_TF,
                  order,
                  fc, f0,
                  Ap, As,
                  b, a);

    // Ensure data are equal to within tolerance
    unsigned int i;
    for (i=0; i<3; i++) {
        CONTEND_DELTA( b[i], b_test[i], tol );
        CONTEND_DELTA( a[i], a_test[i], tol );
    }
}

