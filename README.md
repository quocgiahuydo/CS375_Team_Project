# Plagiarism Detection Using LCS and Jaccard Similarity

A **CS 375 – Design & Analysis of Algorithms** team project that explores two algorithmic approaches for detecting textual plagiarism:

* **Longest Common Subsequence (LCS)**
* **Jaccard Similarity**

The project compares how well each technique identifies textual similarity when passages contain copied content, reordered wording, substitutions, or minor modifications.

## Team Members

* **Harry Do**
* **Justin Mei**

**Course:** CS 375 – Design & Analysis of Algorithms
**University:** Binghamton University

---

## Project Overview

Plagiarism detection can be approached as a problem of measuring similarity between two pieces of text.

This project investigates two different similarity techniques:

### Jaccard Similarity

Jaccard Similarity measures how much vocabulary two documents share.

The text is:

1. Converted to lowercase.
2. Stripped of punctuation.
3. Tokenized into words.
4. Converted into sets of unique words.
5. Compared using set intersection and union.

The similarity score is calculated as:

$$
J(A,B)=\frac{|A\cap B|}{|A\cup B|}
$$

A higher score indicates that the two passages share more vocabulary.

### Longest Common Subsequence

Longest Common Subsequence measures how much of the text appears in the same relative order.

Given two token sequences, LCS finds the longest sequence of words that appears in both while preserving ordering.

For two sequences \(A\) and \(B\):

$$
LCS(i,j)=
\begin{cases}
0 & i=0 \text{ or } j=0 \\
1 + LCS(i-1,j-1) & A_i=B_j \\
\max(LCS(i-1,j),LCS(i,j-1)) & \text{otherwise}
\end{cases}
$$

The implementation uses **dynamic programming with memoization**.

---

## Why Compare Both Algorithms?

Jaccard Similarity and LCS capture different forms of similarity.

| Algorithm              | Best At                                          | Limitation                     |
| ---------------------- | ------------------------------------------------ | ------------------------------ |
| **Jaccard Similarity** | Detecting shared vocabulary                      | Ignores word ordering          |
| **LCS**                | Detecting copied sequences with similar ordering | More computationally expensive |

Using both algorithms provides a broader view of how closely related two passages are.

For example:

* Two passages may use many of the same words but arrange them differently.
* Two passages may preserve much of the same ordering while changing some vocabulary.
* A copied sentence may appear inside a much larger document.

These cases may produce different results depending on which algorithm is used.

---

## Repository Structure

```text
CS375_Team_Project/
├── jaccard.cpp
├── lcs.cpp
├── makefile
│
├── sample.txt
├── sample_sent.txt
├── testcase1.txt
├── testcase2.txt
├── testcase3.txt
├── testcase4.txt
├── testcase5.txt
│
├── Final Report.pdf
├── Plagiarism Detection 375.pdf
├── README.md
│
└── .vscode/
    └── settings.json
```

### Main Files

#### `jaccard.cpp`

Implements the Jaccard Similarity approach.

The program:

* Reads two paragraphs from each test file.
* Normalizes the text.
* Removes punctuation.
* Tokenizes the passages.
* Stores words using `unordered_set`.
* Calculates common words.
* Computes Jaccard Similarity.
* Reports execution time.
* Performs chunk-level comparisons for longer inputs.

#### `lcs.cpp`

Implements the Longest Common Subsequence approach using dynamic programming.

The program:

* Breaks input passages into sentences.
* Tokenizes sentences into words.
* Computes the LCS between token sequences.
* Uses memoization to avoid repeated subproblems.
* Evaluates similarity using different sentence-group sizes.

#### `makefile`

Provides commands for compiling the C++ implementations.

#### Test Files

The repository contains several test cases:

```text
sample.txt
sample_sent.txt
testcase1.txt
testcase2.txt
testcase3.txt
testcase4.txt
testcase5.txt
```

Each input file contains two passages in the following format:

```text
Paragraph A:

<first passage>

Paragraph B:

<second passage>
```

---

## Building the Project

### Requirements

You will need:

* A C++ compiler supporting modern C++
* `g++`
* `make` recommended

Clone the repository:

```bash
git clone https://github.com/quocgiahuydo/CS375_Team_Project.git
cd CS375_Team_Project
```

---

## Compiling

Using `g++`, the programs can be compiled manually.

### Jaccard Similarity

```bash
g++ jaccard.cpp -o jaccard
```

Run with:

```bash
./jaccard
```

### Longest Common Subsequence

```bash
g++ lcs.cpp -o lcs
```

Run with:

```bash
./lcs
```

You can also use the provided `makefile` where applicable.

---

## Jaccard Similarity Pipeline

The Jaccard implementation follows this process:

```text
Input Files
     ↓
Read Paragraph A and Paragraph B
     ↓
Convert Text to Lowercase
     ↓
Remove Punctuation
     ↓
Tokenize Text
     ↓
Store Unique Words in Sets
     ↓
Find Set Intersection
     ↓
Find Set Union
     ↓
Calculate Jaccard Similarity
```

The implementation uses:

```cpp
unordered_set<string>
```

to store unique words.

Because sets are used, repeated occurrences of the same word do not increase the Jaccard score.

---

## Example Jaccard Results

Running the current implementation produces results similar to:

| Test Case         | Overall Jaccard Similarity |
| ----------------- | -------------------------: |
| `sample.txt`      |                     35.90% |
| `sample_sent.txt` |                     54.55% |
| `testcase1.txt`   |                     60.00% |
| `testcase2.txt`   |                     60.00% |
| `testcase3.txt`   |                     50.00% |
| `testcase4.txt`   |                     43.64% |
| `testcase5.txt`   |                     40.00% |

For example, `testcase1.txt` compares sentences similar to:

```text
The quick brown fox jumps over the lazy dog.
```

and:

```text
The quick brown fox jumps over the sleeping cat.
```

The passages share many words while replacing several others, resulting in an overall similarity of approximately:

```text
60.000%
```

---

## Algorithm Complexity

### Jaccard Similarity

Let:

* \(n\) = number of tokens in the first passage
* \(m\) = number of tokens in the second passage

Using hash-based sets, insertion and lookup are approximately constant time on average.

Therefore, the expected complexity is approximately:

### Time Complexity

$$
O(n+m)
$$

### Space Complexity

$$
O(n+m)
$$

This makes Jaccard Similarity suitable for relatively large text inputs.

---

### Longest Common Subsequence

Let:

* \(m\) = number of tokens in the first sequence
* \(n\) = number of tokens in the second sequence

The dynamic programming implementation considers combinations of positions from both sequences.

### Time Complexity

$$
O(mn)
$$

### Space Complexity

$$
O(mn)
$$

LCS therefore provides more information about ordering, but requires significantly more computation and memory than Jaccard Similarity.

---

## Comparison

### Jaccard Similarity

#### Advantages

* Simple to implement
* Fast
* Scales well to larger inputs
* Effective at measuring shared vocabulary
* Word frequency does not artificially increase similarity

#### Limitations

* Ignores word order
* Similar terminology may create false positives
* Significant paraphrasing may reduce the similarity score

---

### Longest Common Subsequence

#### Advantages

* Preserves word ordering
* Effective at detecting copied passages with minor modifications
* Can identify sequences shared between two passages

#### Limitations

* Requires more time and memory
* Full-document comparison can hide smaller copied sections
* Performance decreases as input size grows

---

## Sentence-Level Comparison

One challenge with LCS is that a copied sentence may represent only a small portion of an entire document.

For example:

```text
Document A:
Sentence 1
Sentence 2
Sentence 3
```

may share only:

```text
Sentence 2
```

with another much larger document.

Comparing only entire documents may produce a low similarity score even though a specific passage is strongly related.

For this reason, the project also experiments with comparing smaller groups of sentences.

This allows the algorithm to identify localized similarity that might otherwise be hidden in full-document comparisons.

---

## Chunking

The Jaccard implementation also supports dividing larger inputs into smaller token groups.

The current maximum chunk size is:

```cpp
const size_t MAX_TOKENS = 50;
```

Chunk-level results can help identify local regions where two passages contain unusually similar vocabulary.

The final overall Jaccard score is calculated using the complete token sets of both passages.

---

## Key Findings

The project demonstrates that neither algorithm alone perfectly identifies every form of plagiarism.

Jaccard Similarity performs well when:

* Vocabulary is preserved.
* Word ordering changes.
* Fast comparison is important.

LCS performs well when:

* Word ordering is preserved.
* Small modifications have been made.
* Detecting copied sequences is more important than raw vocabulary overlap.

Using the two measurements together can therefore provide stronger evidence of textual similarity than relying on either method independently.

---

## Possible Improvements

Future improvements could include:

* Combining Jaccard and LCS into a unified similarity score.
* Comparing corresponding multi-sentence windows.
* Supporting user-provided input files from the command line.
* Adding stop-word removal.
* Adding stemming or lemmatization.
* Detecting synonyms and semantic similarity.
* Using n-gram similarity.
* Improving punctuation and sentence parsing.
* Testing on larger datasets.
* Adding automated unit tests.
* Visualizing matched passages.
* Comparing the algorithms against modern embedding-based similarity methods.

---

## Documentation

Additional project information can be found in:

### Final Report

```text
Final Report.pdf
```

Contains the project's motivation, algorithm analysis, methodology, experimental discussion, and conclusions.

### Presentation

```text
Plagiarism Detection 375.pdf
```

Contains the presentation covering:

* Plagiarism detection
* Longest Common Subsequence
* Counterexamples
* Jaccard Similarity
* Algorithm implementation
* Experimental results

---

## Academic Notice

This repository was developed as an academic project for **CS 375 – Design & Analysis of Algorithms at Binghamton University**.

The source code and documentation are provided for educational and portfolio purposes.

Students currently enrolled in CS 375 or a similar course should follow their institution's academic-integrity policies before referencing or reusing any portion of this project.

---

## Authors

**Harry Do**
Computer Science
Binghamton University

**Justin Mei**
Computer Science
Binghamton University

---

## Acknowledgments

* Binghamton University
* Thomas J. Watson College of Engineering and Applied Science
* Department of Computer Science
* CS 375 course staff
