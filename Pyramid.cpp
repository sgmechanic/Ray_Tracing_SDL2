#include "Pyramid.h"
#include <cmath>

Pyramid::Pyramid()
{

}

Pyramid::~Pyramid()
{

}

bool Pyramid::TestIntersections(const Ray& CastRay, LinAlgVector& IntPoint, LinAlgVector& LocalNormal, LinAlgVector& LocalColor)
{
	LinAlgVector BarycentricABC;
	LinAlgVector BarycentricABS;
	LinAlgVector BarycentricACS;
	LinAlgVector BarycentricBCS;

		//Fill matrices according to four plane equations for tetrahedron 
		LinAlgMatrix ABC{ 4,3 };
		ABC.Elem(0, 0) = 0;
		ABC.Elem(1, 0) = 0;
		ABC.Elem(2, 0) = 0;
		ABC.Elem(3, 0) = 1;
		ABC.Elem(0, 1) = 1;
		ABC.Elem(1, 1) = 0;
		ABC.Elem(2, 1) = 0;
		ABC.Elem(3, 1) = 1;
		ABC.Elem(0, 2) = 1.0/2.0;
		ABC.Elem(1, 2) = sqrt(3.0)/2.0;
		ABC.Elem(2, 2) = 0;
		ABC.Elem(3, 2) = 1;
		LinAlgMatrix FirstStepABC = (ABC.Transpose() * ABC);
		FirstStepABC.SimpleInverse();
		LinAlgMatrix ABCFinal = FirstStepABC*(ABC.Transpose());
	
		LinAlgMatrix ABS{ 4,3 };
		ABS.Elem(0, 0) = 0;
		ABS.Elem(1, 0) = 0;
		ABS.Elem(2, 0) = 0;
		ABS.Elem(3, 0) = 1;
		ABS.Elem(0, 1) = 1;
		ABS.Elem(1, 1) = 0;
		ABS.Elem(2, 1) = 0;
		ABS.Elem(3, 1) = 1;
		ABS.Elem(0, 2) = 1.0 / 2.0;
		ABS.Elem(1, 2) = sqrt(3.0) / 6.0;
		ABS.Elem(2, 2) = -sqrt(6.0)/3.0;
		ABS.Elem(3, 2) = 1;
		LinAlgMatrix FirstStepABS = (ABS.Transpose() * ABS);
		FirstStepABS.SimpleInverse();
		LinAlgMatrix ABSFinal = FirstStepABS * (ABS.Transpose());

		LinAlgMatrix ACS{ 4,3 };
		ACS.Elem(0, 0) = 0;
		ACS.Elem(1, 0) = 0;
		ACS.Elem(2, 0) = 0;
		ACS.Elem(3, 0) = 1;
		ACS.Elem(0, 1) = 1.0/2.0;
		ACS.Elem(1, 1) =	sqrt(3.0)/2.0;
		ACS.Elem(2, 1) = 0;
		ACS.Elem(3, 1) = 1;
		ACS.Elem(0, 2) = 1.0 / 2.0;
		ACS.Elem(1, 2) = sqrt(3.0) / 6.0;
		ACS.Elem(2, 2) = -sqrt(6.0) / 3.0;
		ACS.Elem(3, 2) = 1;
		LinAlgMatrix FirstStepACS = (ACS.Transpose() * ACS);
		FirstStepACS.SimpleInverse();
		LinAlgMatrix ACSFinal = FirstStepACS * (ACS.Transpose());

		LinAlgMatrix BCS{ 4,3 };
		BCS.Elem(0, 0) = 1;
		BCS.Elem(1, 0) = 0;
		BCS.Elem(2, 0) = 0;
		BCS.Elem(3, 0) = 1;
		BCS.Elem(0, 1) = 1.0 / 2.0;
		BCS.Elem(1, 1) = sqrt(3.0) / 2.0;
		BCS.Elem(2, 1) = 0;
		BCS.Elem(3, 1) = 1;
		BCS.Elem(0, 2) = 1.0 / 2.0;
		BCS.Elem(1, 2) = sqrt(3.0) / 6.0;
		BCS.Elem(2, 2) = -sqrt(6.0) / 3.0;
		BCS.Elem(3, 2) = 1;
		LinAlgMatrix FirstStepBCS = (BCS.Transpose() * BCS);
		FirstStepBCS.SimpleInverse();
		LinAlgMatrix BCSFinal = FirstStepBCS * (BCS.Transpose());

		Ray BckRay = TransformMatrix.Apply(CastRay, BCKTFORM);

		double ax = BckRay.point1.GetElement(0);
		double ay = BckRay.point1.GetElement(1);
		double az = BckRay.point1.GetElement(2);

		LinAlgVector k = BckRay.ab;
		k.Normalize();
		double kx = k.GetElement(0);
		double ky = k.GetElement(1);
		double kz = k.GetElement(2);

		if (!CloseEnough(kz, 0.0))
		{
			t[0] = -az / kz;
			u[0] = ax + kx * t[0];
			v[0] = ay + ky * t[0];
			w[0] = az + kz * t[0];
			BarycentricABC = ABCFinal * LinAlgVector{ std::vector<double>{u[0],v[0],w[0],1.0}};
			a[0] = BarycentricABC.GetElement(0);
			b[0] = BarycentricABC.GetElement(1);
			c[0] = BarycentricABC.GetElement(2);
		}
		else
		{
			t[0] = 100e6;
			u[0] = 0.0;
			v[0] = 0.0;
			w[0] = 0.0;
			a[0] = -1.0;
			b[0] = -1.0;
			c[0] = -1.0;
		}
		if (!CloseEnough(2 * sqrt(2) * ky + kz, 0.0))
		{
			t[1] = (-az - 2 * sqrt(2) * ay) / (2 * sqrt(2) * ky + kz);
			u[1] = ax + kx * t[1];
			v[1] = ay + ky * t[1];
			w[1] = az + kz * t[1];
			BarycentricABS = ABSFinal * LinAlgVector{ std::vector<double>{u[1],v[1],w[1],1.0} };
			a[1] = BarycentricABS.GetElement(0);
			b[1] = BarycentricABS.GetElement(1);
			c[1] = BarycentricABS.GetElement(2);
		}
		else
		{
			t[1] = 100e6;
			u[1] = 0.0;
			v[1] = 0.0;
			w[1] = 0.0;
			a[1] = -1.0;
			b[1] = -1.0;
			c[1] = -1.0;
		}
		if (!CloseEnough(sqrt(6.0) * kx - sqrt(2.0) * ky + kz, 0.0))
		{
			t[2] = (-sqrt(6.0) * ax + sqrt(2.0) * ay - az) / (sqrt(6.0) * kx - sqrt(2.0) * ky + kz);
			u[2] = ax + kx * t[2];
			v[2] = ay + ky * t[2];
			w[2] = az + kz * t[2];
			BarycentricACS = ACSFinal * LinAlgVector{ std::vector<double>{u[2],v[2],w[2],1.0}};
			a[2] = BarycentricACS.GetElement(0);
			b[2] = BarycentricACS.GetElement(1);
			c[2] = BarycentricACS.GetElement(2);
		}
		else
		{
			t[2] = 100e6;
			u[2] = 0.0;
			v[2] = 0.0;
			w[2] = 0.0;
			a[2] = -1.0;
			b[2] = -1.0;
			c[2] = -1.0;
		}
		if (!CloseEnough(kz - sqrt(6.0) * kx - sqrt(2.0) * ky, 0.0))
		{
			t[3] = (-az + sqrt(6.0) * ax + sqrt(2.0) * ay - sqrt(6.0)) / (kz - sqrt(6.0) * kx - sqrt(2.0) * ky);
			u[3] = ax + kx * t[3];
			v[3] = ay + ky * t[3];
			w[3] = az + kz * t[3];
			BarycentricBCS = BCSFinal * LinAlgVector{ std::vector<double>{u[3],v[3],w[3],1.0} };
			a[3] = BarycentricBCS.GetElement(0);
			b[3] = BarycentricBCS.GetElement(1);
			c[3] = BarycentricBCS.GetElement(2);
		}
		else
		{
			t[3] = 100e6;
			u[3] = 0.0;
			v[3] = 0.0;
			w[3] = 0.0;
			a[2] = -1.0;
			b[2] = -1.0;
			c[2] = -1.0;
		}
		double finalU = 0.0;
		double finalV = 0.0;
		double finalW = 0.0;
		double finalT = 100e6;
		int finalIndex = 0;
		bool ValidIntersection = false;
		for (int i = 0; i < 4; ++i)
		{
			if ((t[i] < finalT) && (t[i] > 0.0) && (a[i] >= 0 && a[i] <= 1 && b[i] >= 0 && b[i] <= 1 && c[i] >= 0 && c[i] <= 1))
			{
				finalT = t[i];
				finalIndex = i;
				finalU = u[i];
				finalV = v[i];
				finalW = w[i];
				ValidIntersection = true;
			}
		}

		if (ValidIntersection)
		{
			LinAlgVector poi = BckRay.point1 + k * finalT;
			LinAlgVector normalVector{ 3 };
			//Now we want to know what normal should we use
			switch (finalIndex)
			{
			case 0:
				normalVector = std::vector<double>{ 0, 0, -1.0 }; 
				break;

			case 1:
				normalVector = std::vector<double>{ 0, -2 * sqrt(2) / 3.0, -1.0 / 3.0 }; 
				break;

			case 2:
				normalVector = std::vector<double>{ sqrt(2.0 / 3.0), -sqrt(2) / 3.0, 1.0 / 3.0 }; 
				break;

			case 3:
				normalVector = std::vector<double>{ sqrt(2.0 / 3.0), sqrt(2) / 3.0, -1.0 / 3.0 }; 
				break;

			}
			IntPoint = TransformMatrix.Apply(poi, FWDTFORM);

			LocalNormal = TransformMatrix.ApplyNorm(normalVector);
			LocalNormal.Normalize();
			LocalColor = BaseColor;
			return true;

		}
		else
		{
			return false;
		}

}
