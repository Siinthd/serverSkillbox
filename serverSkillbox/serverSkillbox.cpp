#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <algorithm>
#include <map>

using namespace std;

string toLower(string text) {
	transform(text.begin(), text.end(), text.begin(), ::tolower);
	return text;
}

map<string, string> database {};

int loadPhrases() {
	ifstream phrases("database.txt"); // ifstream = File Stream, // phrases = переменная
	string line;
	int len = 0;
	while (getline(phrases, line)) { // line = "question $ answer"
		string delimiter = " $ ";
		int pos = line.find(delimiter); // сколько символов с начаала занимает вопрос
		string question = line.substr(0, pos);
		string answer = line.substr(pos + delimiter.length());
		database.insert(pair<string, string>(question, answer));
		len++;
	}
	return len;
}

void savePhrases() {
	// Сохранять фразы в файл
	// Что бы бота можно было научить
	// "Научись: Кто президент США? - Джо Байден" // => добавить в базу вопрос и ответ
}

void bot(string msg) {
	cout << "[BoT]: " << msg << endl;
}

string user() {
	string question;
	cout << "[UseR]: ";
	getline(cin, question);
	question = toLower(question);
	return question;
}

int main() // 0 = все ок
{
	int phraseCount = loadPhrases();
	bot("Hello, I'm SkillBot4000, I can answer " + to_string(phraseCount) + " questions");

	string question;

	while (question != "exit") {
		question = user();
		// Для каждой записи в БД, проверить совпадает ли с вопросом

		for (auto entry : database) { // entry = {"hello", "Hello, hooman!"},
									  // entry.first , .second
			regex pattern(".*" + entry.first + ".*");
			if (regex_match(question, pattern)) 
				bot(entry.second);
			else
				bot("i don't know");
			
		}
	}

}
// ДЗ:
// Добавить больше вопросов и ответов в файл
// Научить бота отвечать "Сорри, не могу ничо сказать" если ответов не нашлось
