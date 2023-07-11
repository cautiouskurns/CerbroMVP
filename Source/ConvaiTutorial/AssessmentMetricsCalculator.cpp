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
