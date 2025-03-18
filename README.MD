# Regex Builder for Accept/Fail Language Classification

## Author
**Dascalu Stefan-Nicolae**

## Design Overview

The goal of this assignment is to generate a regular expression (regex) that accepts all words from the *Accept* language and rejects those from the *Fail* language. The approach carefully balances pattern generalization with precision to ensure that only the correct words are matched.

### Problem Breakdown
- **Input:**  
  The program begins by reading the number of *Accept* words, *Fail* words, and the fixed word length from `input.txt`. These parameters help in organizing the data, and the words are stored in separate lists to clearly distinguish between the two languages.

- **Regex Generation:**  
  - Each word from the *Accept* language initially serves as its own pattern.  
  - The algorithm then attempts to merge these individual patterns by replacing differing characters with `.` (wildcard). This merging is only done when the resulting pattern continues to match all words in the group and does not erroneously match any word from the *Fail* list.  
  - This careful process ensures that the final regex is both generalized and precise, effectively capturing the essence of the *Accept* language.

- **Output:**  
  The final output is written to `output.txt` in a strict format. The first line contains the word `regex`, followed by the generated regular expression on the second line. This format complies with the assignment requirements and makes the output easy to verify.

### Implementation Details
- **Pattern Matching:**  
  The `pattern_match` function is central to the solution. It checks if a given word matches a pattern by treating `.` as a wildcard, which is crucial for verifying that the merged patterns are valid.

- **Pattern Merging:**  
  Functions such as `merge_patterns` and `try_extend_pattern` work together to combine patterns in a controlled manner. They ensure that as new words are considered, the patterns are only extended if they remain consistent with all accepted words and do not conflict with any failed words. This step is key to preventing overgeneralization.

- **Grouping:**  
  Accepted words are organized into groups, each represented by a pattern that is incrementally updated. Merging patterns within groups reduces redundancy and leads to a more compact regex. The final regex is obtained by joining these groups with the union operator (`|`), creating a solution that is both efficient and accurate.

### Code Structure
- **Input/Output Handling:**  
  The solution begins by reading data from `input.txt` and ends by writing the final regex to `output.txt`. This strict adherence to file handling ensures that the program meets the assignment's input/output specifications.

- **Processing:**  
  Each accepted word is processed sequentially. If a word fits an existing pattern group without causing conflicts, it is merged into that group. Otherwise, a new group is created. This methodical process guarantees that every word is properly considered, and the final regex accurately represents the entire *Accept* language.

- **Regex Construction:**  
  Once all words have been processed, the final regex is constructed by concatenating the patterns from each group using the `|` operator. This step consolidates the solution into a single regex that meets all the required criteria, balancing between inclusivity of the *Accept* words and exclusivity of the *Fail* words.
