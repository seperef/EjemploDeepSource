//
// Created by seperef on 15/03/2023.
//

#include "LAMBERTBATTIN.h"
#include "seebatt.h"
#include "seebattk.h"

#include <cmath>
#include <string>

using namespace std;

pair<double, double> lambertbattin(double* ro, double* r, string& dm, double& Dtsec) {
    const double small = 0.000001;
    const double mu = 3.986004418e14; // m3/s2
    double y1 = 0;
    double magr = std::sqrt(r[0] * r[0] + r[1] * r[1] + r[2] * r[2]);
    double magro = std::sqrt(ro[0] * ro[0] + ro[1] * ro[1] + ro[2] * ro[2]);
    double CosDeltaNu = (ro[0] * r[0] + ro[1] * r[1] + ro[2] * r[2]) / (magro * magr);
    double rcrossr[3] = {ro[1] * r[2] - ro[2] * r[1], ro[2] * r[0] - ro[0] * r[2], ro[0] * r[1] - ro[1] * r[0]};
    double magrcrossr = sqrt(rcrossr[0] * rcrossr[0] + rcrossr[1] * rcrossr[1] + rcrossr[2] * rcrossr[2]);
    double SinDeltaNu;
    if (dm == "pro") {
        SinDeltaNu = magrcrossr / (magro * magr);
    } else {
        SinDeltaNu = -magrcrossr / (magro * magr);
    }
    double DNu = atan2(SinDeltaNu, CosDeltaNu);

    // the angle needs to be positive to work for the long way
    if (DNu < 0.0) {
        DNu = 2.0 * M_PI + DNu;
    }

    double RoR = magr / magro;
    double eps = RoR - 1.0;
    double tan2w = 0.25 * eps * eps / (sqrt(RoR) + RoR * (2.0 + sqrt(RoR)));
    double rp = sqrt(magro * magr) * ((cos(DNu * 0.25)) * (cos(DNu * 0.25)) + tan2w);
    double L;
    if (DNu < M_PI) {
        L = ((sin(DNu * 0.25)) * (sin(DNu * 0.25)) + tan2w) /
            ((sin(DNu * 0.25)) * (sin(DNu * 0.25)) + tan2w + cos(DNu * 0.5));
    } else {
        L = ((cos(DNu * 0.25)) * (cos(DNu * 0.25)) + tan2w - cos(DNu * 0.5)) /
            ((cos(DNu * 0.25)) * (cos(DNu * 0.25)) + tan2w);
    }
    double m = mu * Dtsec * Dtsec / (8.0 * rp * rp * rp);
    double x = 10.0;
    double xn = L;
    double chord = std::sqrt(magro * magro + magr * magr - 2.0 * magro * magr * cos(DNu));
    double s = (magro + magr + chord) * 0.5;
    double lim1 = sqrt(m / L);

    while (true) {
        x = xn;
        double tempx = seebatt(x);
        double Denom = 1.0 / (1.0 + 2.0 * x * L) * (4.0 * x + tempx * (3.0 + x));
        double h1 = pow((L + x), 2) * (1.0 + 3.0 * x + tempx) * Denom;
        double h2 = m * (x - L + tempx) * Denom;

        double b = 0.25 * 27.0 * h2 / pow(1.0 + h1, 3);
        if (b < -1.0) {
            // reset the initial condition
            xn = 1.0 - 2.0 * L;
        } else {
            if (y1 > lim1) {
                xn = xn * (lim1 / y1);
            } else {
                double u = 0.5 * b / (1.0 + sqrt(1.0 + b));
                 double k2 = seebattk(u);
                double y = ((1.0 + h1) / 3.0) * (2.0 + sqrt(1.0 + b) / (1.0 + 2.0 * u * k2 * k2));
                xn = sqrt(pow((1.0 - L) * 0.5, 2) + m / (y * y)) - (1.0 + L) * 0.5;
            }
        }
    }
    double y;
    double a = mu * Dtsec * Dtsec / (16.0 * rp * rp * xn * y * y);

// ------------------ Find Eccentric anomalies -----------------
// ------------------------ Hyperbolic -------------------------
    if (a < -small) {
        double arg1 = sqrt(s / (-2.0 * a));
        double arg2 = sqrt((s - chord) / (-2.0 * a));
        // ------- Evaluate f and g functions --------
        double AlpH = 2.0 * asinh(arg1);
        double BetH = 2.0 * asinh(arg2);
        double DH = AlpH - BetH;
        double F = 1.0 - (a / magro) * (1.0 - cosh(DH));
        double GDot = 1.0 - (a / magr) * (1.0 - cosh(DH));
        double G = Dtsec - sqrt(-a * a * a / mu) * (sinh(DH) - DH);
    } else {
        // ------------------------ Elliptical ---------------------
        if (a > small) {
            double arg1 = sqrt(s / (2.0 * a));
            double arg2 = sqrt((s - chord) / (2.0 * a));
            double Sinv = arg2;
            double Cosv = sqrt(1.0 - (magro + magr - chord) / (4.0 * a));
            double BetE = 2.0 * asin(Sinv);
            if (DNu > M_PI) {
                BetE = -BetE;
            }
            Cosv = sqrt(1.0 - s / (2.0 * a));
            Sinv = arg1;
            double am = s * 0.5;
            double ae = M_PI;
            double be = 2.0 * asin(sqrt((s - chord) / s));
            double tm = sqrt(am * am * am / mu) * (ae - (be - sin(be)));
            double AlpE;
            if (Dtsec > tm) {
                AlpE = 2.0 * M_PI - 2.0 * asin(Sinv);
            } else {
                AlpE = 2.0 * asin(Sinv);
            }
            double DE = AlpE - BetE;
            double F = 1.0 - (a / magro) * (1.0 - cos(DE));
            double GDot = 1.0 - (a / magr) * (1.0 - cos(DE));
            double G = Dtsec - sqrt(a * a * a / mu) * (DE - sin(DE));
        } else {
// --------------------- Parabolic ---------------------
            double arg1 = 0.0;
            double arg2 = 0.0;
            throw ("a parabolic orbit");
        }


    }
    double G;
    double F;
    double GDot;
    double vo[] = {};
    double v[] = {};
    for (int i = 0; i < 3; i++) {
        vo[i] = (r[i] - F * ro[i]) / G;
        v[i] = (GDot * r[i] - ro[i]) / G;
    }
}