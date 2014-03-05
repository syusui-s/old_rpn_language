////////////////////////////////////
// element.h 
// functions for class Element
////////////////////////////////////
/*
#define INTEGER  int
#define FLOATING double


bool is_dig(char input);
bool is_dec(char input);
bool is_capital(char input);
bool is_small(char input);
bool is_alphabet(char input);
std::string ltoa(long input);
std::string ftoa(double input);
bool is_num(std::string input);
bool is_int(std::string input);
bool is_float(std::string input);
bool is_alphastr(std::string input);
bool is_op(std::string input);
std::string rtntype(std::string input);
Element** elementarray(std::list<std::string> input);
int findop(Element** input,int length);
Element** take_elements(Element** elements, int pos, int num);
int op_num(std::string op);
Element* op_plus(Element* op1,Element* op2);
Element* op_minus(Element* op1,Element* op2);
Element* op_multiply(Element* op1,Element* op2);
Element* op_divide(Element* op1,Element* op2);
Element* op_modulo(Element* op1,Element* op2);
Element* fn_absolute(Element* op);
Element* fn_pm(Element* op);
Element* fn_inverse(Element* op);
Element* fn_pow(Element* op1,Element* op2);
Element* fn_square(Element* op1);
Element* fn_cube(Element* op1);
Element* fn_sqrt(Element* op1);
Element* fn_cbrt(Element* op1);
Element* fn_print(Element *op1);
Element* calc_elements(Element** elementarray, std::string op);
Element** del_array(Element** input, int length, int pos, int num);
Element** ins_element(Element **inp_arr, Element* inp_elm, int length, int pos);
Element** calc_array(Element** x, int length);
std::string calclate(std::string input);
*/

// type_of
// it returns type of input data.
// "unknown","opfunc","bool","int","float","rational","complex","char","string","variable","constant"
////////////////////////////////////
// 文字列変換用関数 
////////////////////////////////////

// is_dig[1-9] 数字だったら、trueを返す関数
bool is_dig(char input) {
	return '0' <= input && input <= '9';
}

// is_dec(.) 小数点
bool is_dec(char input){
	return input=='.';
}

// is_captital 大文字だったら、true
bool is_capital(char input){	return 'A' <= input && input <= 'Z';
}

// is_small 小文字だったら、true
bool is_small(char input){
	return 'a' <= input && input <= 'z';
}

// is_alphabet
bool is_alphabet(char input){
	return is_capital(input) || is_small(input);
}

// ltoa
// 整数を文字列に変換し、それを返す
std::string ltoa(long input){
	std::stringstream ss;
	ss << input;
	return ss.str();
}

// ftoa
// 実数を文字列に変換し、それを返す
std::string ftoa(double input){
	std::stringstream ss;
	ss << input;
	return ss.str();
}


// is_num
// 数字かどうかチェック（動作チェック済み）
bool is_num(std::string input){
	unsigned int i=0;
	bool rtn=true;
	if(!is_dig(input[0]) && input[0]!='-' && input[0]!='+') rtn = false;
	for(i=1;i<input.length();i++){
		if(!is_dig(input[i]) && !is_dec(input[i])){
			rtn=false;
			break;
		}
	}
	return rtn;
}



// is_int
// 整数かどうかチェック（動作チェック済み）
bool is_int(std::string input){
	unsigned int i;

	if(input[1]=='.') return false;
	if(input[0]=='0' && input.length()>1){
		throw((std::string)"0から始まる整数値は表記できません。0を表記する場合は、0を1つのみ入力するようにしてください。");
	}
	if(!is_dig(input[0]) && input[0]!='-' && input[0]!='+') return false; // 一文字目が数字でも-,+でもなければ、false
	for(i=1;i<input.length();i++){
		if(!is_dig(input[i])) return false;
	}
	return true;
}



// is_float（動作チェック済み）
// 小数かどうかチェック
bool is_float(std::string input){
	unsigned int i;
	bool dec=false;

	for(i=0;i<input.length();i++){
		if(is_dec(input[i]) && dec){
			throw((std::string)"小数点を2個以上指定することはできません。");
			return false;
		}
		if(!is_dig(input[i]) && !is_dec(input[i])) return false;
		if(is_dec(input[i])) dec=true;

		if(dec && input.length()==1){
			//「.」のみの小数は扱えません
			return false;
		}
	}
	return true;
}



// is_alphastr
// 英文字列かチェック（動作チェック済み）
bool is_alphastr(std::string input){
	unsigned int i;

	for(i=0;i<input.length();i++){
		if(!is_alphabet(input[i])){
			return false;
		}
	}
	return true;
}


// abs pm pw ^2 ^3 sqrt cbrt lg ln log sin cos tan csc sec cot
// is_op
// 演算子かどうかをチェック
bool is_op(std::string input){
	std::string op[]={
		// 二項演算子
		"+","-","*","/","mod",
		// 単項演算子
		"abs","pm","1/x","inv",
		// 指数関数
		"pow","^2","^3","sqrt","cbrt",
		// 対数関数
		"lg","ln","log",
		// 三角関数
		"sin","cos","tan","csc","sec","cot",
		// IO
		"print"
	};
	unsigned int i,n=sizeof(op)/sizeof(op[0]);

	for(i=0;i<n;i++){
		if(input==op[i]) return true;
	}

	return false;
}

// rtntype
// 受け取った文字列を元に、型を返す関数
// unknown 不明要素
// op, func 演算要素
// int, float, complex,rational 数値要素
// variable 変数要素
std::string rtntype(std::string input){
	int n=0;
	std::string type[]={"unknown","op","int","float","complex","rational","variable","constant"};

	if(is_op(input)){
		n=1;
	/*}else if(is_func(input)){
		n=2;*/
	}else if(is_num(input)){
		if(is_int(input)) n=2;
		else if(is_float(input)) n=3;
		// else if(is_complex(input)) n=4;
		// else if(is_rational(input)) n=5
	}

	return type[n];
}

// Class Element
// it deals with various types.
class Element{
private:
	std::string data;
	std::string type;

public:
	Element(std::string);
	~Element();
	// データを返す関数
	std::string data_is(void) const;
	// 中身の型を返す関数
	std::string type_is(void) const;
	
	// convert
	/*
	INTEGER  to_int();
	FLOATING to_float();
	*/
};

Element::Element(std::string input){
	data = input;
	type = rtntype(input);
}

std::string Element::data_is(void) const{
	return data;
}

std::string Element::type_is(void) const{
	return type;
}

/////////////////////////////////////////////////////////////////////////////
// elementarray
// splitで、文字列のリストとなった入力値を、要素の「配列」に変換する関数（テスト済み）
Element** elementarray(std::list<std::string> input){
	int i;
	std::list<std::string>::iterator it = input.begin();
	Element **elements = new Element*[input.size()];

	for(i=0;i<(int)input.size();i++){
		elements[i] = new Element(*it);

		if(elements[i]->type_is() == "unknown"){
			throw((std::string)"要素 '"+(std::string)*it+(std::string)"' を評価できませんでした");
		}
		it++;
	}

	//std::cout << (elements[0])->data_is() << std::endl;

	return elements;
}

// findop
// 要素配列の、演算子が初めに現れる位置を返す。（テスト済み）
int findop(Element** input,int length){
	int i,output=-1;

	for(i=0;i<length;i++){
		//std::cout << i + " ";
		#if MYDEBUG
		std::cout << input[i]->data_is() << ".type_is() --->" << input[i]->type_is() << std::endl;
		#endif

		if((input[i]->type_is()) == "op"){
			output=i;
			break;
		}
	}
	if(output==-1) throw((std::string)"演算子が見つかりませんでした。");

	return output;
}

/////////////////////////////////////////////////////////////////////////////
// take_elements
// 配列から、指定された位置から、指定された個数だけ、抽出して、配列として返す。
//                     (要素の配列)        (開始位置) (抽出個数)
Element** take_elements(Element** elements, int pos, int num){
	int i;
	Element **output = new Element*[num];

	for(i=pos;i<pos+num;i++){
		output[i-pos] = elements[i];
	}
	return output;
}

/////////////////////////////////////////////////////////////////////////////
// op_num
// 演算子のオペランド数を返す
int op_num(std::string op){
	// 二項演算子
	if(op=="+") return 2;
	if(op=="-") return 2;
	if(op=="/") return 2;
	if(op=="*") return 2;
	if(op=="mod") return 2;
	
	// 単項演算子
	if(op=="abs") return 1;
	if(op=="pm") return 1;
	if(op=="1/x" || op=="inv") return 1;

	// 指数関数
	if(op=="pow") return 2;
	if(op=="^2") return 1;
	if(op=="^3") return 1;
	if(op=="sqrt") return 1;
	if(op=="cbrt") return 1;
	
	// 対数関数
	if(op=="lg") return 1;
	if(op=="ln") return 1;
	if(op=="log") return 2;

	// 三角関数
	if(op=="sin") return 1;
	if(op=="cos") return 1;
	if(op=="tan") return 1;
	if(op=="csc") return 1;
	if(op=="sec") return 1;
	if(op=="cot") return 1;
	// if(op=="arcsin") return 1;

	// 
	if(op=="print") return 1;

	return 0;
}


/* -------------- 演算用関数 -------------- */

/////////////////////////////////////////////////////////////////////////////
// 二項演算子　＋
Element* op_plus(Element* op1,Element* op2){
	long a;
	double b;
	Element *rtn;
	
	if(op1->type_is() == "int" && op2->type_is() == "int"){
		a = atol(op1->data_is().c_str()) + atol(op2->data_is().c_str());
		rtn = new Element(ltoa(a));
	}else if(op1->type_is() == "float" || op2->type_is() == "float"){
		b = atof(op1->data_is().c_str()) + atof(op2->data_is().c_str());
		rtn = new Element(ftoa(b));
	}
	return rtn;
}

/////////////////////////////////////////////////////////////////////////////
// 二項演算子　−
Element* op_minus(Element* op1,Element* op2){
	long a;
	double b;
	Element *rtn;
	
	if(op1->type_is() == "int" && op2->type_is() == "int"){
		a = atol(op1->data_is().c_str()) - atol(op2->data_is().c_str());
		rtn = new Element(ltoa(a));
	}else if(op1->type_is() == "float" || op2->type_is() == "float"){
		b = atof(op1->data_is().c_str()) - atof(op2->data_is().c_str());
		rtn = new Element(ftoa(b));
	}

	return rtn;
}

/////////////////////////////////////////////////////////////////////////////
// 二項演算子　＊
Element* op_multiply(Element* op1,Element* op2){
	long a;
	double b;
	Element *rtn;
	
	if(op1->type_is() == "int" && op2->type_is() == "int"){
		a = atol(op1->data_is().c_str()) * atol(op2->data_is().c_str());
		rtn = new Element(ltoa(a));
	}else if(op1->type_is() == "float" || op2->type_is() == "float"){
		b = atof(op1->data_is().c_str()) * atof(op2->data_is().c_str());
		rtn = new Element(ftoa(b));
	}

	return rtn;
}

/////////////////////////////////////////////////////////////////////////////
// 二項演算子　／
Element* op_divide(Element* op1,Element* op2){
	//long a;
	double b;
	Element *rtn;
	
	b = atof(op1->data_is().c_str()) / atof(op2->data_is().c_str());
	rtn = new Element(ftoa(b));

	return rtn;
}

/////////////////////////////////////////////////////////////////////////////
// 二項演算子　MOD
Element* op_modulo(Element* op1,Element* op2){
	long a;
	double b;
	Element *rtn;
	
	if(op1->type_is() == "int" && op2->type_is() == "int"){
		a = atol(op1->data_is().c_str()) % atol(op2->data_is().c_str());
		rtn = new Element(ltoa(a));
	}else if(op1->type_is() == "float" || op2->type_is() == "float"){
		b = fmod(atof(op1->data_is().c_str()), atof(op2->data_is().c_str()));
		rtn = new Element(ftoa(b));
	}

	return rtn;
}

/////////////////////////////////////////////////////////////////////////////
// 関数 絶対値ABS
Element* fn_absolute(Element* op){
	long a;
	double b;
	Element *rtn;
	
	if(op->type_is() == "int"){
		a = atol(op->data_is().c_str());
		if(a<0) a*=-1;
		rtn = new Element(ltoa(a));
	}else if(op->type_is() == "float"){
		b = atof(op->data_is().c_str());
		if(b<0) b*=-1;
		rtn = new Element(ftoa(b));
	}

	return rtn;
}

/////////////////////////////////////////////////////////////////////////////
// 関数 +/-
Element* fn_pm(Element* op){
	long a;
	double b;
	Element *rtn;
	
	if(op->type_is() == "int"){
		a = atol(op->data_is().c_str());
		a*=-1;
		rtn = new Element(ltoa(a));
	}else if(op->type_is() == "float"){
		b = atof(op->data_is().c_str());
		b*=-1;
		rtn = new Element(ftoa(b));
	}

	return rtn;
}

/////////////////////////////////////////////////////////////////////////////
// 関数 逆数
Element* fn_inverse(Element* op){
	//long a;
	double b;
	Element *rtn;
	
	b = atof(op->data_is().c_str());
	rtn = new Element(ftoa(1.0/b));

	return rtn;
}

Element* fn_pow(Element* op1,Element* op2){
	double b;
	Element *rtn;
	
	b = std::pow(atof(op1->data_is().c_str()), atof(op2->data_is().c_str()));
	rtn = new Element(ftoa(b));

	return rtn;
}

// ^2 ^3 sqrt cbrt lg ln log sin cos tan csc sec cot
Element* fn_square(Element* op1){
	double b;
	Element *rtn;
	
	b = std::pow(atof(op1->data_is().c_str()),2.0);
	rtn = new Element(ftoa(b));

	return rtn;
}

//
Element* fn_cube(Element* op1){
	double b;
	Element *rtn;
	
	b = std::pow(atof(op1->data_is().c_str()),3.0);
	rtn = new Element(ftoa(b));

	return rtn;
}

Element* fn_sqrt(Element* op1){
	double b;
	Element *rtn;
	
	b = std::sqrt(atof(op1->data_is().c_str()));
	rtn = new Element(ftoa(b));

	return rtn;
}

Element* fn_cbrt(Element* op1){
	double b;
	Element *op2;
	
	//b = cbrtf(atof(op1->data_is().c_str()));
	//rtn = new Element(ftoa(b));
	op2 = new Element("0.333333333"); // あとで修正

	return fn_pow(op1,op2);
}

Element* fn_print(Element *op1){
	std::cout << "==> " << op1->data_is() << std::endl;
	return new Element("0");
}

/////////////////////////////////////////////////////////////////////////////
// calc_elements
// 要素の配列（Element**）と演算子（string）を渡すと、計算結果を返す。
Element* calc_elements(Element** elementarray, std::string op){
	Element* rtn;
	if(op=="+") rtn = op_plus(elementarray[0],elementarray[1]);
	else if(op=="-") rtn = op_minus(elementarray[0],elementarray[1]);
	else if(op=="*") rtn = op_multiply(elementarray[0],elementarray[1]);
	else if(op=="/") rtn = op_divide(elementarray[0],elementarray[1]);
	else if(op=="mod") rtn = op_modulo(elementarray[0],elementarray[1]);
	else if(op=="abs") rtn = fn_absolute(elementarray[0]);
	else if(op=="pm") rtn = fn_pm(elementarray[0]);
	else if(op=="1/x" || op=="inv") rtn = fn_inverse(elementarray[0]);
	else if(op=="pow") rtn = fn_pow(elementarray[0],elementarray[1]);
	else if(op=="^2") rtn = fn_square(elementarray[0]);
	else if(op=="^3") rtn = fn_cube(elementarray[0]);
	else if(op=="sqrt") rtn = fn_sqrt(elementarray[0]);
	else if(op=="cbrt") rtn = fn_cbrt(elementarray[0]);
	else if(op=="print") rtn = fn_print(elementarray[0]);
	else throw((std::string)"この演算子、もしくは関数はまだ定義されていません。");

	return rtn;
}

// del_array
// pos以降、num個の配列のみを削除する
Element** del_array(Element** input, int length, int pos, int num){
	// 入力配列 Element** input
	// 入力のサイズ int length <- 配列のサイズを指定
	// 削除開始位置 int pos    <- 開始位置なので、演算子の個数を
	// 削除個数     int num    <- 演算子を含める場合は、呼び出し時に引数に+1する。

	int i,j;
	Element **rtn = new Element*[length-num];

	for(i=0;i<pos;i++) rtn[i] = input[i];
	j = i;

	for(;i<pos+num;i++){
		// delete input[i];
	}

	for(i=pos+num;i<length;i++){
		rtn[j] = input[i];
		j++;
	}

	return rtn;
}

// ins_element
// inp_arrのposの位置にinp_elmを挿入する
Element** ins_element(Element **inp_arr, Element* inp_elm, int length, int pos){
	int i;
	Element **rtn = new Element*[length+1];
	
	for(i=0;i<pos;i++) rtn[i] = inp_arr[i];
	rtn[i] = inp_elm;
	#if MYDEBUG
	std::cout << "debug:" << inp_elm->data_is() << std::endl;
	#endif
	// ここで、iはrtnに合わせる
	for(i=i+1;i<length+1;i++) rtn[i] = inp_arr[i-1];
	
	return rtn;
}

// calc_array
// 要素の配列、すなわち式を渡すと、計算結果を返す。
Element** calc_array(Element** x, int length){
	Element* ins;
	int pos=0;
	int numop=0;

	if(length == 1){
		
	}

	while(length > 1){
		pos=-1;
		pos = findop(x,length); //	演算子の位置をposに代入
		numop = op_num(x[pos]->data_is()); // オペランド数を調べる
		if(pos-numop<0) throw((std::string)"書式が間違っています。演算子の位置がおかしいようです。");
		ins = calc_elements(take_elements(x, pos-numop, numop),x[pos]->data_is()); // 演算子とオペランドをcalc_elementsに渡し、計算結果を得る
		pos-=numop; // 削除および挿入の開始位置を指定
		x = ins_element(del_array(x,length,pos,numop+1), ins, length-numop-1, pos);
		length-=numop; // 計算後の配列の長さをlengthに代入
	}
	return x;
}

// calclate
std::string calclate(std::string input){
	int length;
	std::list<std::string> strlst;
	Element *rtn;
	
	try{
		strlst = split(delsp(input)); // 入力値を文字列リストに変換
		length = strlst.size(); // 文字列リストの大きさをlengthに代入

		Element **elements = elementarray(strlst);

		rtn = calc_array(elements,length)[0];
	}
	catch(std::string errormsg){
		std::cout << "エラー: " << errormsg;
		rtn = new Element("");
	}

	return rtn->data_is();
}



