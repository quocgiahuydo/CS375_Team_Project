#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

double LCS(const vector<string>& a, const vector<string>& b, int i, int j, vector<vector<double>>& A) {
	if (i == 0 || j == 0) return 0;
	if (A[i][j] != -1) return A[i][j];

	if (a[i - 1] == b[j - 1]) return A[i][j] = 1 + LCS(a, b, i - 1, j - 1, A);

	return A[i][j] = max(LCS(a, b, i - 1, j, A), LCS(a, b, i, j - 1, A));
}

double LCS(const vector<string>& a, const vector<string>& b) {
	vector<vector<double>> A(a.size() + 1, vector<double>(b.size() + 1, -1));
	return LCS(a, b, a.size(), b.size(), A);
}

string trim(const string& s) {
	size_t first = 0;
	while (first < s.size() && isspace(static_cast<unsigned char>(s[first]))) first++;

	size_t last = s.size();
	while (last > first && isspace(static_cast<unsigned char>(s[last - 1]))) last--;

	return s.substr(first, last - first);
}

vector<string> parseSentence(const string& sentence) {
	vector<string> words;
	string word;
	stringstream ss(sentence);

	while (ss >> word) words.push_back(word);

	return words;
}

vector<string> parse(const string& text) {
	vector<string> sens;
	string sentence;
	stringstream ss(text);

	while (getline(ss, sentence, '.')) {
		sentence = trim(sentence);
		if (!sentence.empty()) sens.push_back(sentence);
	}
	return sens;
}

vector<string> flatten(const vector<string>& sentences) {
	vector<string> words;
	for (const auto& s : sentences) {
		vector<string> w = parseSentence(s);
		words.insert(words.end(), w.begin(), w.end());
	}
	return words;
}

double similarity(string& a, string& b, int size=-1) {
	vector<string> sa = parse(a);
	vector<string> sb = parse(b);

	if (sa.empty() || sb.empty()) return 0.0;

	if (size == -1 || size > sa.size()) size = sa.size();

	double maximum = 0.0;

	for (int i = 0; i < sb.size() && i < sa.size(); i += size) {
		vector<string> wa = parseSentence(sa[i]);
		int end = min(i + size, (int) sb.size());
		vector<string> slice(sb.begin() + i, sb.begin() + end);
		vector<string> wb = flatten(slice);

		if (wa.empty() || wb.empty()) continue;

		double lcs = LCS(wa, wb);
		maximum = max(lcs / wb.size(), maximum);
	}

	return maximum;
}

int main() {
	string a = "Gatsby believed in the green light, the orgastic future that year by year recedes before us. It eluded us then, but that’s no matter—tomorrow we will run faster, stretch out our arms farther. And one fine morning——So we beat on, boats against the current, borne back ceaselessly into the past.";
	string b = "Gatsby trusted in the green light, the orgiastic future that year by year slips away from us. It escaped us then, but that is no matter—tomorrow we will run faster, reach our arms farther. And one bright morning—So we press on, boats against the current, carried back endlessly into the past.";
	// third parameter is size of substrings in sentences
	cout << similarity(a, b) << '\n';
	cout << similarity(a, b, 1) << '\n';
	cout << similarity(a, b, 2) << '\n';
}
