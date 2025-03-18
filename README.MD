# Classifier – Regex Generation for Accept and Fail Languages

## Author
**Dascalu Stefan-Nicolae**

## Design Overview

The goal of this assignment is to generate a regular expression (regex) that accepts all words from the *Accept* language and rejects those from the *Fail* language.

### Problem Breakdown
- **Input:**  
  Read the number of *Accept* words, *Fail* words, and the fixed word length from `input.txt`. Store the words in separate lists.
  
- **Regex Generation:**  
  - Start by treating each accepted word as an individual pattern.
  - Attempt to merge patterns by replacing differing characters with `.` (wildcard) if the new pattern:
    - Matches all words in the group.
    - Does not match any word from the *Fail* list.
    
- **Output:**  
  Write the output in `output.txt` with the first line as `regex` and the second line containing the generated regex.

### Implementation Details
- **Pattern Matching:**  
  The `pattern_match` function checks if a word matches a given pattern, interpreting `.` as a wildcard.

- **Pattern Merging:**  
  Functions like `merge_patterns` and `try_extend_pattern` are used to combine patterns, ensuring that merged patterns remain valid.

- **Grouping:**  
  Accepted words are grouped, and their patterns are merged to form a final regex by joining groups with the union operator (`|`).

### Code Structure
- **Input/Output Handling:**  
  Reads from `input.txt` and writes the final regex to `output.txt`.
- **Processing:**  
  Each accepted word is either merged into an existing group or starts a new group based on pattern compatibility.
- **Regex Construction:**  
  Final patterns are combined to create the overall regex.
