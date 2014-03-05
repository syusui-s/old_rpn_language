////////////////////////////////////
// typeenum.h
////////////////////////////////////

// EType
// プログラム内で扱う要素型を扱いやすいようにenumで列挙しています。
typedef enum {
	// [不明要素] 不明要素 T_Unknown
	T_Unknown,
	// [演算要素] 演算子要素 T_Op, 関数要素 T_Func
	T_Op, T_Func,
	// [数値要素] 整数要素 T_Int, 浮動小数点要素 T_Float, 複素数要素 T_Complex, 有理数要素 T_Rational
	T_Int, T_Float, T_Complex, T_Rational,
	// [変数要素] T_Variable
	T_Variable,
	// [定数要素] T_Constant
	T_Constant
}EType;
