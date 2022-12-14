#pragma once
#include "Vector2.h"
#include "Vector3.h"

namespace Solas {
	struct Matrix3x3 {
		Vector3 rows[3]; //[3][3]

		Matrix3x3() = default;
		Matrix3x3(const Vector3& row1, const Vector3& row2, const Vector3& row3);

		Vector3 operator [] (size_t index) const { return rows[index]; }
		Vector3& operator [] (size_t index) { return rows[index]; }

		Vector2 operator * (const Vector2& v);
		Matrix3x3 operator * (const Matrix3x3& mx);

		static Matrix3x3 CreateScale(const Vector2& scale);
		static Matrix3x3 CreateScale(float scale);

		static Matrix3x3 CreateRotation(float rad);

		static Matrix3x3 CreateTranslation(const Vector2& translate);

		static const Matrix3x3 identity;
		static const Matrix3x3 zero;
		//bro, im so sleepy imma go "schmee-mee-mee-mee-mee-mee-mee" and i dont even care
		//I did not write this
	};

	inline Matrix3x3::Matrix3x3(const Vector3& row1, const Vector3& row2, const Vector3& row3) {
		rows[0] = row1;
		rows[1] = row2;
		rows[2] = row3;
	}

	inline Vector2 Matrix3x3::operator*(const Vector2& v) {
		Vector2 result;
		result.x = v.x * rows[0][0] + v.y * rows[0][1] + 1.0f * rows[0][2];
		result.y = v.x * rows[1][0] + v.y * rows[1][1] + 1.0f * rows[1][2];

		return result;
	}

	inline Matrix3x3 Matrix3x3::operator*(const Matrix3x3& mx) {
		Matrix3x3 result;
		//row 1
		result[0][0] = rows[0][0] * mx[0][0] + rows[0][1] * mx[1][0] + rows[0][2] * mx[2][0];
		result[0][1] = rows[0][0] * mx[0][1] + rows[0][1] * mx[1][1] + rows[0][2] * mx[2][1];
		result[0][2] = rows[0][0] * mx[0][2] + rows[0][1] * mx[1][2] + rows[0][2] * mx[2][2];

		//row 2
		result[1][0] = rows[1][0] * mx[0][0] + rows[1][1] * mx[1][0] + rows[1][2] * mx[2][0];
		result[1][1] = rows[1][0] * mx[0][1] + rows[1][1] * mx[1][1] + rows[1][2] * mx[2][1];
		result[1][2] = rows[1][0] * mx[0][2] + rows[1][1] * mx[1][2] + rows[1][2] * mx[2][2];

		//row 3
		result[2][0] = rows[2][0] * mx[0][0] + rows[2][1] * mx[1][0] + rows[2][2] * mx[2][0];
		result[2][1] = rows[2][0] * mx[0][1] + rows[2][1] * mx[1][1] + rows[2][2] * mx[2][1];
		result[2][2] = rows[2][0] * mx[0][2] + rows[2][1] * mx[1][2] + rows[2][2] * mx[2][2];

		return result;
	}

	inline Matrix3x3 Matrix3x3::CreateScale(const Vector2& scale) {
		//non-uniform
		//sx 0 0
		//0 sy 0
		//0 0 1
		Matrix3x3 mx = identity;
		mx[0][0] = scale.x;
		mx[1][1] = scale.y;

		return mx;
	}

	inline Matrix3x3 Matrix3x3::CreateScale(float scale) {
		//uniform
		Matrix3x3 mx = identity;
		mx[0][0] = scale;
		mx[1][1] = scale;

		return mx;
	}

	inline Matrix3x3 Matrix3x3::CreateRotation(float rad) {
		Matrix3x3 mx;

		mx[0] = Vector3{ std::cos(rad), -std::sin(rad), 0.0f };
		mx[1] = Vector3{ std::sin(rad), std::cos(rad), 0.0f };
		mx[2] = Vector3{ 0.0f, 0.0f, 1.0f };

		return mx;
	}

	inline Matrix3x3 Matrix3x3::CreateTranslation(const Vector2& translate) {
		Matrix3x3 mx = identity;
		mx[0][2] = translate.x;
		mx[1][2] = translate.y;


		return mx;
	}
}