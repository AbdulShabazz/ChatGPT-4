Text.Summarization.Algorithm.in.Javascript.md

## Perplexity AI Pro v2.22.0

**Q:** Provide a Javascript algorithm that summarizes text. Do not rely on third party libraries although databases are acceptable.

**A:** Here is a simple JavaScript algorithm to summarize text without relying on third-party libraries. This algorithm uses a frequency-based approach to identify the most important sentences in a given text.

### Step-by-Step Algorithm

1. **Split the text into sentences.**
2. **Tokenize each sentence into words.**
3. **Calculate the frequency of each word.**
4. **Score each sentence based on the frequency of its words.**
5. **Select the top sentences to form the summary.**

### Implementation

```javascript
function summarizeText(text, numberOfSentences) {
    // Step 1: Split the text into sentences
    const sentences = text.match(/[^\.!\?]+[\.!\?]+/g);
    if (!sentences) return "";

    // Step 2: Tokenize each sentence into words
    const wordFrequency = {};
    const words = text.toLowerCase().match(/\b\w+\b/g);

    // Step 3: Calculate the frequency of each word
    words.forEach(word => {
        if (wordFrequency[word]) {
            wordFrequency[word]++;
        } else {
            wordFrequency[word] = 1;
        }
    });

    // Step 4: Score each sentence based on the frequency of its words
    const sentenceScores = sentences.map(sentence => {
        const sentenceWords = sentence.toLowerCase().match(/\b\w+\b/g);
        let score = 0;
        sentenceWords.forEach(word => {
            if (wordFrequency[word]) {
                score += wordFrequency[word];
            }
        });
        return { sentence, score };
    });

    // Step 5: Select the top sentences to form the summary
    sentenceScores.sort((a, b) => b.score - a.score);
    const summarySentences = sentenceScores.slice(0, numberOfSentences).map(item => item.sentence);

    return summarySentences.join(' ');
}

// Example usage
const text = "Your long text goes here. It can be multiple sentences. The algorithm will summarize it.";
const numberOfSentences = 2;
const summary = summarizeText(text, numberOfSentences);
console.log(summary);
```

### Explanation

1. **Splitting the Text**: The text is split into sentences using a regular expression that matches sentence-ending punctuation.
2. **Tokenizing Words**: Each sentence is tokenized into words, and all words are converted to lowercase to ensure case insensitivity.
3. **Calculating Word Frequency**: A frequency dictionary is created to count the occurrences of each word.
4. **Scoring Sentences**: Each sentence is scored based on the sum of the frequencies of its words.
5. **Selecting Top Sentences**: The sentences are sorted by their scores, and the top `numberOfSentences` are selected to form the summary.

This algorithm provides a basic yet effective way to summarize text by focusing on the most frequently occurring words and the sentences that contain them.

Sources

[1] text-summarization · GitHub Topics https://github.com/topics/text-summarization?l=javascript

[2] transitive-bullshit/text-summarization: Automagically ... - GitHub https://github.com/transitive-bullshit/text-summarization

[3] A simple node module that allows users to summarize text - GitHub https://github.com/SwapnikKatkoori/node-summarizer

[4] How to Summarize Text with JavaScript in 5 minutes? - Eden AI https://www.edenai.co/post/how-to-use-text-summarization-api-with-javascript-in-5-minutes

[5] wkallhof/js-summarize: An NLP Summarizer built with Javascript. https://github.com/wkallhof/js-summarize

[6] python - What are the available tools to summarize or simplify text? https://stackoverflow.com/questions/5479333/what-are-the-available-tools-to-summarize-or-simplify-text

[7] Node.js | AI Text Summarization in 5 minutes! - YouTube https://www.youtube.com/watch?v=OqSRqrkkCuw

[8] Summarizer Website using MEAN Stack - DEV Community https://dev.to/siddheshuncodes/summarizer-website-using-mean-stack-5hbj

[9] Text summarisation in TypeScript with Transformers.js https://blanchardjulien.com/posts/transformers_js/

[10] 4 Powerful Long Text Summarization Methods With Real Examples https://www.width.ai/post/4-long-text-summarization-methods

[11] Text Summarization - EvaDB 0.3.9 https://evadb.readthedocs.io/en/stable/source/usecases/text-summarization.html

[12] I've been exploring the best way to summarize documents with LLMs ... https://www.reddit.com/r/LangChain/comments/165xmzx/ive_been_exploring_the_best_way_to_summarize/

[13] Are there any good free GPT-powered AI summarizer for very long ... https://www.reddit.com/r/ChatGPTPro/comments/14eprse/are_there_any_good_free_gptpowered_ai_summarizer/

[14] Summarizing and extracting structured data from long text - Prompting https://community.openai.com/t/summarizing-and-extracting-structured-data-from-long-text/453078

[15] Some API or any helpful tool/repo for doing a text summary https://softwarerecs.stackexchange.com/questions/84979/some-api-or-any-helpful-tool-repo-for-doing-a-text-summary

[16] Summarize Text - LangChain.js https://js.langchain.com/v0.2/docs/tutorials/summarization/

[17] Show a summary text/image from URL - javascript - Stack Overflow https://stackoverflow.com/questions/24851539/show-a-summary-text-image-from-url

[18] How to send long articles for summarization? - API https://community.openai.com/t/how-to-send-long-articles-for-summarization/205574

[19] GPT Summarizing Database Tables - API - OpenAI Developer Forum https://community.openai.com/t/gpt-summarizing-database-tables/80813

[20] Vanilla JavaScript and HTML - No frameworks. No libraries. No ... https://dev.to/pluralsight/vanilla-javascript-and-html-no-frameworks-no-libraries-no-problem-2n99

**Q:** Are nouns scored only? Since, obviously we intend to discount pronouns and infinitives, such as I, We, You and The!

**A:** In text summarization algorithms, nouns are not the only words that are scored. Typically, the scoring process involves calculating the frequency of all significant words in the text, which usually includes nouns, verbs, adjectives, and adverbs, while excluding common stopwords such as pronouns, conjunctions, prepositions, and articles.

### Key Points from the Sources:

1. **Frequency-Based Scoring**:
   - The algorithm involves creating a frequency table for words in the text, excluding common stopwords like pronouns and articles[1][6].
   - Words are scored based on their frequency, and these scores are used to evaluate the importance of sentences[1][6].

2. **Exclusion of Stopwords**:
   - Common stopwords, including pronouns (e.g., I, we, you) and articles (e.g., the), are typically excluded from the frequency table to focus on more meaningful words[1][6].

3. **Sentence Scoring**:
   - Sentences are scored based on the cumulative frequency of the significant words they contain[1][2][6].
   - This approach ensures that sentences with higher concentrations of important words are prioritized in the summary.

4. **Evaluation Metrics**:
   - Evaluation of summarization systems often involves metrics like ROUGE, which measure the overlap of n-grams (including nouns, verbs, etc.) between the generated summary and reference summaries[3].

### Example Algorithm:

Here is a refined version of the previous JavaScript algorithm, explicitly excluding pronouns and infinitives:

```javascript
function summarizeText(text, numberOfSentences) {
    // List of common stopwords to exclude
    const stopwords = new Set([
        "i", "we", "you", "he", "she", "it", "they", "me", "him", "her", "us", "them",
        "my", "your", "his", "her", "its", "our", "their", "mine", "yours", "hers", "ours", "theirs",
        "the", "a", "an", "to", "in", "on", "at", "by", "for", "with", "about", "against", "between", "into", "through", "during", "before", "after", "above", "below", "from", "up", "down", "out", "over", "under", "again", "further", "then", "once", "here", "there", "when", "where", "why", "how", "all", "any", "both", "each", "few", "more", "most", "other", "some", "such", "no", "nor", "not", "only", "own", "same", "so", "than", "too", "very", "s", "t", "can", "will", "just", "don", "should", "now"
    ]);

    // Step 1: Split the text into sentences
    const sentences = text.match(/[^\.!\?]+[\.!\?]+/g);
    if (!sentences) return "";

    // Step 2: Tokenize each sentence into words
    const wordFrequency = {};
    const words = text.toLowerCase().match(/\b\w+\b/g);

    // Step 3: Calculate the frequency of each word, excluding stopwords
    words.forEach(word => {
        if (!stopwords.has(word)) {
            if (wordFrequency[word]) {
                wordFrequency[word]++;
            } else {
                wordFrequency[word] = 1;
            }
        }
    });

    // Step 4: Score each sentence based on the frequency of its words
    const sentenceScores = sentences.map(sentence => {
        const sentenceWords = sentence.toLowerCase().match(/\b\w+\b/g);
        let score = 0;
        sentenceWords.forEach(word => {
            if (wordFrequency[word]) {
                score += wordFrequency[word];
            }
        });
        return { sentence, score };
    });

    // Step 5: Select the top sentences to form the summary
    sentenceScores.sort((a, b) => b.score - a.score);
    const summarySentences = sentenceScores.slice(0, numberOfSentences).map(item => item.sentence);

    return summarySentences.join(' ');
}

// Example usage
const text = "Your long text goes here. It can be multiple sentences. The algorithm will summarize it.";
const numberOfSentences = 2;
const summary = summarizeText(text, numberOfSentences);
console.log(summary);
```

This algorithm ensures that the summarization process focuses on the most meaningful words by excluding common stopwords, including pronouns and infinitives, thereby improving the quality of the summary.

Sources

[1] 5 Powerful Text Summarization Techniques in Python. - Turing https://www.turing.com/kb/5-powerful-text-summarization-techniques-in-python

[2] [PDF] Sentence-Level Extractive Text Summarization https://web.stanford.edu/class/archive/cs/cs224n/cs224n.1194/reports/custom/15790001.pdf

[3] How do I evaluate a text summarization tool? - Stack Overflow https://stackoverflow.com/questions/9879276/how-do-i-evaluate-a-text-summarization-tool

[4] Combined Method of Analyzing Anaphoric Pronouns and Inter ... https://link.springer.com/chapter/10.1007/978-3-319-18476-0_8

[5] Infinitives - Purdue OWL https://owl.purdue.edu/owl/general_writing/mechanics/gerunds_participles_and_infinitives/infinitives.html

[6] NLP — Text Summarization using NLTK: TF-IDF Algorithm https://towardsdatascience.com/text-summarization-using-tf-idf-e64a0644ace3

[7] Verb Forms: "-ing," Infinitives, and Past Participles - Grammar https://academicguides.waldenu.edu/writingcenter/grammar/verbforms

[8] Noun–Pronoun Agreement - Grammar - Academic Guides https://academicguides.waldenu.edu/writingcenter/grammar/nounpronounagreement

[9] Using Gerunds and Infinitives - University of Toronto - Writing Advice https://advice.writing.utoronto.ca/english-language/gerunds/

[10] [PDF] The Use of the Infinitive - ERIC https://files.eric.ed.gov/fulltext/ED598862.pdf

[11] Infinitives and noun stems - how do you handle them in your ... - Reddit https://www.reddit.com/r/conlangs/comments/1273rlx/infinitives_and_noun_stems_how_do_you_handle_them/

[12] Pronoun Generation for Text Summarization and Question Answering https://www.researchgate.net/publication/228355287_Pronoun_Generation_for_Text_Summarization_and_Question_Answering
