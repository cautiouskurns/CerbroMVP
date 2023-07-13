// Fill out your copyright notice in the Description page of Project Settings.


#include "AssessmentMetricsCalculator.h"


// Calculate total times a question has been asked in a set of questions
int32 UAssessmentMetricsCalculator::CalculateTimesAskedForQuestions(const TArray<FTest>& Questions)
{
    int32 TotalTimesAsked = 0;
    for (const FTest& Question : Questions)
    {
        TotalTimesAsked += Question.TimesTested;
    }
    return TotalTimesAsked;
}

// Calculate total times questions have been asked in a subtopic
int32 UAssessmentMetricsCalculator::CalculateTimesAskedForSubtopic(const FSubtopic& Subtopic)
{
    return CalculateTimesAskedForQuestions(Subtopic.Questions);
}

// Calculate total times questions have been asked in a topic
int32 UAssessmentMetricsCalculator::CalculateTimesAskedForTopic(const FTopic& Topic)
{
    int32 TotalTimesAsked = 0;
    for (const FSubtopic& Subtopic : Topic.Subtopics)
    {
        TotalTimesAsked += CalculateTimesAskedForSubtopic(Subtopic);
    }
    return TotalTimesAsked;
}

// Calculate total times questions have been asked in a section
int32 UAssessmentMetricsCalculator::CalculateTimesAskedForSection(const FSectionStruct& Section)
{
    int32 TotalTimesAsked = 0;
    for (const FTopic& Topic : Section.Topics)
    {
        TotalTimesAsked += CalculateTimesAskedForTopic(Topic);
    }
    return TotalTimesAsked;
}

// Calculate total times questions have been asked in a subject
int32 UAssessmentMetricsCalculator::CalculateTimesAskedForSubject(const FSubjectStruct& Subject)
{
    int32 TotalTimesAsked = 0;
    for (const FSectionStruct& Section : Subject.SubjectDetailsArray)
    {
        TotalTimesAsked += CalculateTimesAskedForSection(Section);
    }
    return TotalTimesAsked;
}

// INCREMENTAL REFACTORING FUNCTIONS
// Calculate total times questions have been asked for a specific subtopic, given its title
int32 UAssessmentMetricsCalculator::CalculateTimesAskedForSubtopicIR(const FString& SubtopicTitle, const TArray<FSubjectStruct>& SubjectDataArray)
{
    for (const FSubjectStruct& Subject : SubjectDataArray)
    {
        for (const FSectionStruct& Section : Subject.SubjectDetailsArray)
        {
            for (const FTopic& Topic : Section.Topics)
            {
                for (const FSubtopic& Subtopic : Topic.Subtopics)
                {
                    if (Subtopic.Title == SubtopicTitle)
                    {
                        return CalculateTimesAskedForQuestions(Subtopic.Questions);
                    }
                }
            }
        }
    }

    return 0; // Return 0 if no subtopic with the given title is found
}


// Calculate total times a question has been asked in a set of questions
int32 UAssessmentMetricsCalculator::CalculateTimesAskedForQuestionsIndividual(const TArray<FTest>& Questions)
{
    int32 TotalTimesAsked = 0;
    for (const FTest& Question : Questions)
    {
        TotalTimesAsked += Question.TimesTested;
    }
    return TotalTimesAsked;
}

int32 UAssessmentMetricsCalculator::CalculateTimesAskedForQuestionIR(const FString& QuestionText, const TArray<FSubjectStruct>& SubjectDataArray)
{
    for (const FSubjectStruct& Subject : SubjectDataArray)
    {
        for (const FSectionStruct& Section : Subject.SubjectDetailsArray)
        {
            for (const FTopic& Topic : Section.Topics)
            {
                for (const FSubtopic& Subtopic : Topic.Subtopics)
                {
                    for (const FTest& Question : Subtopic.Questions)
                    {
                        if (Question.Question == QuestionText)
                        {
                            return CalculateTimesAskedForQuestionsIndividual(Subtopic.Questions);
                        }
                    }

                }
            }
        }
    }

    return 0; // Return 0 if no subtopic with the given title is found
}




// Helper function to calculate total times correct for a set of questions
int32 UAssessmentMetricsCalculator::CalculateTimesCorrectForQuestions(const TArray<FTest>& Questions)
{

    int32 TotalTimesCorrect = 0;
    for (const FTest& Question : Questions)
    {
        TotalTimesCorrect += Question.TimesCorrect;
    }
    return TotalTimesCorrect;
}

// Calculate total times questions have been answered correctly in a subtopic
int32 UAssessmentMetricsCalculator::CalculateTimesCorrectForSubtopic(const FSubtopic& Subtopic)
{
    return CalculateTimesCorrectForQuestions(Subtopic.Questions);
}

// Calculate total times questions have been answered correctly in a topic
int32 UAssessmentMetricsCalculator::CalculateTimesCorrectForTopic(const FTopic& Topic)
{
    int32 TotalTimesCorrect = 0;
    for (const FSubtopic& Subtopic : Topic.Subtopics)
    {
        TotalTimesCorrect += CalculateTimesCorrectForSubtopic(Subtopic);
    }
    return TotalTimesCorrect;
}

// Calculate total times questions have been answered correctly in a section
int32 UAssessmentMetricsCalculator::CalculateTimesCorrectForSection(const FSectionStruct& Section)
{
    int32 TotalTimesCorrect = 0;
    for (const FTopic& Topic : Section.Topics)
    {
        TotalTimesCorrect += CalculateTimesCorrectForTopic(Topic);
    }
    return TotalTimesCorrect;
}

// Calculate total times questions have been answered correctly in a subject
int32 UAssessmentMetricsCalculator::CalculateTimesCorrectForSubject(const FSubjectStruct& Subject)
{
    int32 TotalTimesCorrect = 0;
    for (const FSectionStruct& Section : Subject.SubjectDetailsArray)
    {
        TotalTimesCorrect += CalculateTimesCorrectForSection(Section);
    }
    return TotalTimesCorrect;
}


// INCREMENTAL REFACTORING FUNCTION
// Calculate total times questions have been answered correctly for a specific subtopic, given its title
int32 UAssessmentMetricsCalculator::CalculateTimesCorrectForSubtopicIR(const FString& SubtopicTitle, const TArray<FSubjectStruct>& SubjectDataArray)
{
    for (const FSubjectStruct& Subject : SubjectDataArray)
    {
        for (const FSectionStruct& Section : Subject.SubjectDetailsArray)
        {
            for (const FTopic& Topic : Section.Topics)
            {
                for (const FSubtopic& Subtopic : Topic.Subtopics)
                {
                    if (Subtopic.Title == SubtopicTitle)
                    {
                        return CalculateTimesCorrectForQuestions(Subtopic.Questions);
                    }
                }
            }
        }
    }

    return 0; // Return 0 if no subtopic with the given title is found
}





int32 UAssessmentMetricsCalculator::UpdateTimesCorrectForQuestion(FTest& Question, const FString& SelectedAnswer)
{
    if (SelectedAnswer == Question.CorrectAnswer)
    {
        // print that answers are the same to screen
        Question.TimesCorrect++;
        return Question.TimesCorrect;
    }
    return -1;
}

int32 UAssessmentMetricsCalculator::UpdateTimesCorrectForSubtopic(FSubtopic& Subtopic, int32 QuestionIndex, const FString& SelectedAnswer)
{
    if (Subtopic.Questions.IsValidIndex(QuestionIndex))
    {
        FTest& SelectedQuestion = Subtopic.Questions[QuestionIndex];
        return UpdateTimesCorrectForQuestion(SelectedQuestion, SelectedAnswer);
    }
    return -1;
}

int32 UAssessmentMetricsCalculator::UpdateTimesCorrectForTopic(FTopic& Topic, int32 SubtopicIndex, int32 QuestionIndex, const FString& SelectedAnswer)
{
    if (Topic.Subtopics.IsValidIndex(SubtopicIndex))
    {
        FSubtopic& SelectedSubtopic = Topic.Subtopics[SubtopicIndex];
        return UpdateTimesCorrectForSubtopic(SelectedSubtopic, QuestionIndex, SelectedAnswer);
    }
    return -1;
}

int32 UAssessmentMetricsCalculator::UpdateTimesCorrectForSection(FSectionStruct& Section, int32 TopicIndex, int32 SubtopicIndex, int32 QuestionIndex, const FString& SelectedAnswer)
{
    if (Section.Topics.IsValidIndex(TopicIndex))
    {
        FTopic& SelectedTopic = Section.Topics[TopicIndex];
        return UpdateTimesCorrectForTopic(SelectedTopic, SubtopicIndex, QuestionIndex, SelectedAnswer);
    }
    return -1;
}

int32 UAssessmentMetricsCalculator::UpdateTimesCorrectForSubject(FSubjectStruct& Subject, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, int32 QuestionIndex, const FString& SelectedAnswer)
{
    if (Subject.SubjectDetailsArray.IsValidIndex(SectionIndex))
    {
        FSectionStruct& SelectedSection = Subject.SubjectDetailsArray[SectionIndex];
        return UpdateTimesCorrectForSection(SelectedSection, TopicIndex, SubtopicIndex, QuestionIndex, SelectedAnswer);
    }
    return -1;
}

int32 UAssessmentMetricsCalculator::UpdateTimesCorrect(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, int32 QuestionIndex, const FString& SelectedAnswer, TArray<FSubjectStruct>& SubjectDataArray)
{
    if (SubjectDataArray.IsValidIndex(SubjectIndex))
    {
        FSubjectStruct& SelectedSubject = SubjectDataArray[SubjectIndex];
        return UpdateTimesCorrectForSubject(SelectedSubject, SectionIndex, TopicIndex, SubtopicIndex, QuestionIndex, SelectedAnswer);
    }
    return -1;
}




// INCREMENTAL REFACTORING FUNCTIONS

// UpdateTimesTestedForQuestion: Increments the TimesTested property of the question and returns the new value.
int32 UAssessmentMetricsCalculator::UpdateTimesTestedForQuestion(FTest& Question)
{
    Question.TimesTested++;
    return Question.TimesTested;
}

// UpdateTimesTestedForSubtopic: Checks if the question index is valid and if so, delegates to UpdateTimesTestedForQuestion().
int32 UAssessmentMetricsCalculator::UpdateTimesTestedForSubtopic(FSubtopic& Subtopic, int32 QuestionIndex)
{
    if (Subtopic.Questions.IsValidIndex(QuestionIndex))
    {
        return UpdateTimesTestedForQuestion(Subtopic.Questions[QuestionIndex]);
    }
    return -1;
}

// UpdateTimesTestedForTopic: Checks if the subtopic index is valid and if so, delegates to UpdateTimesTestedForSubtopic().
int32 UAssessmentMetricsCalculator::UpdateTimesTestedForTopic(FTopic& Topic, int32 SubtopicIndex, int32 QuestionIndex)
{
    if (Topic.Subtopics.IsValidIndex(SubtopicIndex))
    {
        return UpdateTimesTestedForSubtopic(Topic.Subtopics[SubtopicIndex], QuestionIndex);
    }
    return -1;
}

// UpdateTimesTestedForSection: Checks if the topic index is valid and if so, delegates to UpdateTimesTestedForTopic().
int32 UAssessmentMetricsCalculator::UpdateTimesTestedForSection(FSectionStruct& Section, int32 TopicIndex, int32 SubtopicIndex, int32 QuestionIndex)
{
    if (Section.Topics.IsValidIndex(TopicIndex))
    {
        return UpdateTimesTestedForTopic(Section.Topics[TopicIndex], SubtopicIndex, QuestionIndex);
    }
    return -1;
}

// UpdateTimesTestedForSubject: Checks if the section index is valid and if so, delegates to UpdateTimesTestedForSection().
int32 UAssessmentMetricsCalculator::UpdateTimesTestedForSubject(FSubjectStruct& Subject, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, int32 QuestionIndex)
{
    if (Subject.SubjectDetailsArray.IsValidIndex(SectionIndex))
    {
        return UpdateTimesTestedForSection(Subject.SubjectDetailsArray[SectionIndex], TopicIndex, SubtopicIndex, QuestionIndex);
    }
    return -1;
}

int32 UAssessmentMetricsCalculator::UpdateRandomQuestionTimesTested(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, int32 QuestionIndex, TArray<FSubjectStruct>& SubjectDataArray)
{
    if (SubjectDataArray.IsValidIndex(SubjectIndex))
    {
        return UpdateTimesTestedForSubject(SubjectDataArray[SubjectIndex], SectionIndex, TopicIndex, SubtopicIndex, QuestionIndex);
    }
    return -1;
}




// UpdateTimesTestedAndCorrectForQuestion: Increments the TimesTested and, if the answer is correct, TimesCorrect properties of the question with the given text and returns the new values.
FTest UAssessmentMetricsCalculator::UpdateTimesTestedAndCorrectForQuestion(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText, const FString& SelectedAnswer, TArray<FSubjectStruct>& SubjectDataArray)
{
    if (SubjectDataArray.IsValidIndex(SubjectIndex))
    {
        FSubjectStruct& Subject = SubjectDataArray[SubjectIndex];
        if (Subject.SubjectDetailsArray.IsValidIndex(SectionIndex))
        {
            FSectionStruct& Section = Subject.SubjectDetailsArray[SectionIndex];
            if (Section.Topics.IsValidIndex(TopicIndex))
            {
                FTopic& Topic = Section.Topics[TopicIndex];
                if (Topic.Subtopics.IsValidIndex(SubtopicIndex))
                {
                    FSubtopic& Subtopic = Topic.Subtopics[SubtopicIndex];
                    for (FTest& Question : Subtopic.Questions)
                    {
                        if (Question.Question == QuestionText)
                        {
                            Question.TimesTested++;
                            if (SelectedAnswer == Question.CorrectAnswer)
                            {
                                Question.TimesCorrect++;
                            }
                            return Question;
                        }
                    }
                }
            }
        }
    }
    return FTest(); // Return an empty FTest struct if no question with the given text is found
}



FString UAssessmentMetricsCalculator::SubmitAnswer(const FString& AnswerText)
{
    SubmittedAnswer = AnswerText;

    return SubmittedAnswer;
}

FTest UAssessmentMetricsCalculator::UpdateAnswerStatus(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText, TArray<FSubjectStruct>& SubjectDataArray)
{
    if (!SubjectDataArray.IsValidIndex(SubjectIndex)) return FTest();
    FSubjectStruct& SelectedSubject = SubjectDataArray[SubjectIndex];
    if (!SelectedSubject.SubjectDetailsArray.IsValidIndex(SectionIndex)) return FTest();
    FSectionStruct& SelectedSection = SelectedSubject.SubjectDetailsArray[SectionIndex];
    if (!SelectedSection.Topics.IsValidIndex(TopicIndex)) return FTest();
    FTopic& SelectedTopic = SelectedSection.Topics[TopicIndex];
    if (!SelectedTopic.Subtopics.IsValidIndex(SubtopicIndex)) return FTest();
    FSubtopic& SelectedSubtopic = SelectedTopic.Subtopics[SubtopicIndex];
    for (FTest& Question : SelectedSubtopic.Questions)
    {
       /* FString DebugMessage = FString::Printf(TEXT("Question: %s, Answer: %s"), *Question.Question, *SubmittedAnswer);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, DebugMessage);*/

        if (Question.Question == QuestionText)
        {
            //FString DebugMessage = FString::Printf(TEXT("Questions are equal"));
            //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, DebugMessage);

            Question.TimesTested++;

            // print times tested
            FString DebugMessage = FString::Printf(TEXT("Times Tested: %d"), Question.TimesTested);
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, DebugMessage);

            if (SubmittedAnswer == Question.CorrectAnswer)
            {
                Question.TimesCorrect++;
            }
            return Question;
        }
    }
    return FTest(); // Return an empty FTest if no question with the given text is found
}


// New function to get the number of times a specific question has been tested
int32 UAssessmentMetricsCalculator::GetTimesTestedForQuestion(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText, TArray<FSubjectStruct>& SubjectDataArray)
{
    if (!SubjectDataArray.IsValidIndex(SubjectIndex)) return -1;
    FSubjectStruct& SelectedSubject = SubjectDataArray[SubjectIndex];
    if (!SelectedSubject.SubjectDetailsArray.IsValidIndex(SectionIndex)) return -1;
    FSectionStruct& SelectedSection = SelectedSubject.SubjectDetailsArray[SectionIndex];
    if (!SelectedSection.Topics.IsValidIndex(TopicIndex)) return -1;
    FTopic& SelectedTopic = SelectedSection.Topics[TopicIndex];
    if (!SelectedTopic.Subtopics.IsValidIndex(SubtopicIndex)) return -1;
    FSubtopic& SelectedSubtopic = SelectedTopic.Subtopics[SubtopicIndex];
    for (FTest& Question : SelectedSubtopic.Questions)
    {
        if (Question.Question == QuestionText)
        {
            return Question.TimesTested;
        }
    }
    return -1; // Return -1 if no question with the given text is found
}

// New function to get the number of times a specific question has been answered correctly
int32 UAssessmentMetricsCalculator::GetTimesCorrectForQuestion(int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText, TArray<FSubjectStruct>& SubjectDataArray)
{
    if (!SubjectDataArray.IsValidIndex(SubjectIndex)) return -1;
    FSubjectStruct& SelectedSubject = SubjectDataArray[SubjectIndex];
    if (!SelectedSubject.SubjectDetailsArray.IsValidIndex(SectionIndex)) return -1;
    FSectionStruct& SelectedSection = SelectedSubject.SubjectDetailsArray[SectionIndex];
    if (!SelectedSection.Topics.IsValidIndex(TopicIndex)) return -1;
    FTopic& SelectedTopic = SelectedSection.Topics[TopicIndex];
    if (!SelectedTopic.Subtopics.IsValidIndex(SubtopicIndex)) return -1;
    FSubtopic& SelectedSubtopic = SelectedTopic.Subtopics[SubtopicIndex];
    for (FTest& Question : SelectedSubtopic.Questions)
    {
        if (Question.Question == QuestionText)
        {
            return Question.TimesCorrect;
        }
    }
    return -1; // Return -1 if no question with the given text is found
}