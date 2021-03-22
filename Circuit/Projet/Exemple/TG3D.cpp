#include "TG3D.h";

TG3D::TG3D(void) {
	for (int l = 0; l < 4; ++l)
	{
		for (int c = 0; c < 4; ++c)
		{
			mat[l][c] = (l == c) ? 1.0F : 0.0F;
		}
	}
}

TG3D TG3D::mult(const TG3D& rhs)
{
	TG3D res;
	for (int l = 0; l < 4; ++l)
	{
		for (int c = 0; c < 4; ++c)
		{
			res.mat[l][c] = 0.0F;
			for (int k = 0; k < 4; ++k)
			{ // [l][k] *[k][c]
				res.mat[l][c] += this->mat[l][k] * rhs.mat[k][c];
			}
		}
	}
	return res;
}
