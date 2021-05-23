#include"FormatD.h"

FormatD::FormatD() {};

//  type == 1 ±íÊ¾Æ¥ÅäÊı×Ö    2 Æ¥Åä×ÖÄ¸
bool FormatD::isCorrect(string aimStr, int type) {
	regex reg_num("^[0-9]+$");
	regex reg_letter("^[a-zA-Z]+$");
	bool res_one;
	bool res_two;
	switch (type) {
	case 1:
		res_one = regex_match(aimStr, reg_num);
		if (res_one) {
			return true;
		}
		else {
			return false;
		}
		break;
	case 2:
		res_two = regex_match(aimStr, reg_letter);
		if (res_two) {
			return true;
		}
		else {
			return false;
		}
		break;
	default:
		cout << "form default" << endl;
	}
}