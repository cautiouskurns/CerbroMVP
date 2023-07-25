// Fill out your copyright notice in the Description page of Project Settings.


#include "ConvaiTutorial/MetricHandling/AssessmentMetricsCalculator.h"


UAssessmentMetricsCalculator::UAssessmentMetricsCalculator(UObject* ObjectInitializer, UUserInteractionDataManager* manager)
{
    UserInteractionDataManager = manager;
}


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


int32 UAssessmentMetricsCalculator::CalculateTimesAskedForSubtopicIR(const FString& SubtopicTitle, const TArray<FFieldStruct>& FieldDataArray)
{
    for (const FFieldStruct& Field : FieldDataArray)
    {
        for (const FAreaStruct& Area : Field.Areas)
        {
            for (const FSubjectGroupStruct& SubjectGroup : Area.SubjectGroups)
            {
                for (const FSubjectStruct& Subject : SubjectGroup.Subjects)
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
            }
        }
    }

    return 0; // Return 0 if no subtopic with the given title is found
}










// Calculate total times questions have been asked in a subtopic
int32 UAssessmentMetricsCalculator::CalculateTimesAskedForSubtopicInteract(const FString& SubtopicName, UUserInteractionDataManager* UserInteractionDataManagerLocal)
{
    int32 TotalTimesAsked = 0;

    const FUserInteractionData& UserInteractions = UserInteractionDataManagerLocal->GetUserInteractions();

    for (const auto& FieldPair : UserInteractions.Fields)
    {
        for (const auto& AreaPair : FieldPair.Value.Areas)
        {
            for (const auto& SubjectGroupPair : AreaPair.Value.SubjectGroups)
            {
                for (const auto& SubjectPair : SubjectGroupPair.Value.Subjects)
                {
                    for (const auto& SectionPair : SubjectPair.Value.Sections)
                    {
                        for (const auto& TopicPair : SectionPair.Value.Topics)
                        {
                            for (const auto& SubtopicPair : TopicPair.Value.Subtopics)
                            {
                                if (SubtopicPair.Key == SubtopicName)
                                {
                                    for (const auto& QuestionPair : SubtopicPair.Value.Questions)
                                    {
                                        TotalTimesAsked += QuestionPair.Value.TimesAsked;
                                    }
                                    return TotalTimesAsked;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 0; // Return 0 if no subtopic with the given name is found
}


// Calculate total times questions have been asked in a topic
int32 UAssessmentMetricsCalculator::CalculateTimesAskedForTopicInteract(const FString& TopicName, UUserInteractionDataManager* UserInteractionDataManagerLocal)
{
    int32 TotalTimesAsked = 0;

    const FUserInteractionData& UserInteractions = UserInteractionDataManagerLocal->GetUserInteractions();

    for (const auto& FieldPair : UserInteractions.Fields)
    {
        for (const auto& AreaPair : FieldPair.Value.Areas)
        {
            for (const auto& SubjectGroupPair : AreaPair.Value.SubjectGroups)
            {
                for (const auto& SubjectPair : SubjectGroupPair.Value.Subjects)
                {
                    for (const auto& SectionPair : SubjectPair.Value.Sections)
                    {
                        for (const auto& TopicPair : SectionPair.Value.Topics)
                        {
                            if (TopicPair.Key == TopicName)
                            {
                                for (const auto& SubtopicPair : TopicPair.Value.Subtopics)
                                {
                                    for (const auto& QuestionPair : SubtopicPair.Value.Questions)
                                    {
                                        TotalTimesAsked += QuestionPair.Value.TimesAsked;
                                    }
                                }
                                return TotalTimesAsked;
                            }
                        }
                    }
                }
            }
        }
    }

    return 0; // Return 0 if no topic with the given name is found
}

int32 UAssessmentMetricsCalculator::CalculateTimesAskedForSectionInteract(const FString& SectionName, UUserInteractionDataManager* UserInteractionDataManagerLocal)
{
    int32 TotalTimesAsked = 0;

    const FUserInteractionData& UserInteractions = UserInteractionDataManagerLocal->GetUserInteractions();

    for (const auto& FieldPair : UserInteractions.Fields)
    {
        for (const auto& AreaPair : FieldPair.Value.Areas)
        {
            for (const auto& SubjectGroupPair : AreaPair.Value.SubjectGroups)
            {
                for (const auto& SubjectPair : SubjectGroupPair.Value.Subjects)
                {
                    for (const auto& SectionPair : SubjectPair.Value.Sections)
                    {
                        if (SectionPair.Key == SectionName)
                        {
                            for (const auto& TopicPair : SectionPair.Value.Topics)
                            {
                                for (const auto& SubtopicPair : TopicPair.Value.Subtopics)
                                {
                                    for (const auto& QuestionPair : SubtopicPair.Value.Questions)
                                    {
                                        TotalTimesAsked += QuestionPair.Value.TimesAsked;
                                    }
                                }
                            }
                            return TotalTimesAsked;
                        }
                    }
                }
            }
        }
    }

    return 0; // Return 0 if no section with the given name is found
}

int32 UAssessmentMetricsCalculator::CalculateTimesAskedForSubjectInteract(const FString& SubjectName, UUserInteractionDataManager* UserInteractionDataManagerLocal)
{
    int32 TotalTimesAsked = 0;

    const FUserInteractionData& UserInteractions = UserInteractionDataManagerLocal->GetUserInteractions();

    for (const auto& FieldPair : UserInteractions.Fields)
    {
        for (const auto& AreaPair : FieldPair.Value.Areas)
        {
            for (const auto& SubjectGroupPair : AreaPair.Value.SubjectGroups)
            {
                for (const auto& SubjectPair : SubjectGroupPair.Value.Subjects)
                {
                    if (SubjectPair.Key == SubjectName)
                    {
                        for (const auto& SectionPair : SubjectPair.Value.Sections)
                        {
                            for (const auto& TopicPair : SectionPair.Value.Topics)
                            {
                                for (const auto& SubtopicPair : TopicPair.Value.Subtopics)
                                {
                                    for (const auto& QuestionPair : SubtopicPair.Value.Questions)
                                    {
                                        TotalTimesAsked += QuestionPair.Value.TimesAsked;
                                    }
                                }
                            }
                        }
                        return TotalTimesAsked;
                    }
                }
            }
        }
    }

    return 0; // Return 0 if no subject with the given name is found
}

int32 UAssessmentMetricsCalculator::CalculateTimesAskedForSubjectGroupInteract(const FString& SubjectGroupName, UUserInteractionDataManager* UserInteractionDataManagerLocal)
{
    int32 TotalTimesAsked = 0;

    const FUserInteractionData& UserInteractions = UserInteractionDataManagerLocal->GetUserInteractions();

    for (const auto& FieldPair : UserInteractions.Fields)
    {
        for (const auto& AreaPair : FieldPair.Value.Areas)
        {
            for (const auto& SubjectGroupPair : AreaPair.Value.SubjectGroups)
            {
                if (SubjectGroupPair.Key == SubjectGroupName)
                {
                    for (const auto& SubjectPair : SubjectGroupPair.Value.Subjects)
                    {
                        for (const auto& SectionPair : SubjectPair.Value.Sections)
                        {
                            for (const auto& TopicPair : SectionPair.Value.Topics)
                            {
                                for (const auto& SubtopicPair : TopicPair.Value.Subtopics)
                                {
                                    for (const auto& QuestionPair : SubtopicPair.Value.Questions)
                                    {
                                        TotalTimesAsked += QuestionPair.Value.TimesAsked;
                                    }
                                }
                            }
                        }
                    }
                    return TotalTimesAsked;
                }
            }
        }
    }

    return 0; // Return 0 if no subject group with the given name is found
}

int32 UAssessmentMetricsCalculator::CalculateTimesAskedForAreaInteract(const FString& AreaName, UUserInteractionDataManager* UserInteractionDataManagerLocal)
{
    int32 TotalTimesAsked = 0;

    const FUserInteractionData& UserInteractions = UserInteractionDataManagerLocal->GetUserInteractions();

    for (const auto& FieldPair : UserInteractions.Fields)
    {
        for (const auto& AreaPair : FieldPair.Value.Areas)
        {
            if (AreaPair.Key == AreaName)
            {
                for (const auto& SubjectGroupPair : AreaPair.Value.SubjectGroups)
                {
                    for (const auto& SubjectPair : SubjectGroupPair.Value.Subjects)
                    {
                        for (const auto& SectionPair : SubjectPair.Value.Sections)
                        {
                            for (const auto& TopicPair : SectionPair.Value.Topics)
                            {
                                for (const auto& SubtopicPair : TopicPair.Value.Subtopics)
                                {
                                    for (const auto& QuestionPair : SubtopicPair.Value.Questions)
                                    {
                                        TotalTimesAsked += QuestionPair.Value.TimesAsked;
                                    }
                                }
                            }
                        }
                    }
                }
                return TotalTimesAsked;
            }
        }
    }

    return 0; // Return 0 if no area with the given name is found
}

int32 UAssessmentMetricsCalculator::CalculateTimesAskedForFieldInteract(const FString& FieldName, UUserInteractionDataManager* UserInteractionDataManagerLocal)
{
    int32 TotalTimesAsked = 0;

    const FUserInteractionData& UserInteractions = UserInteractionDataManagerLocal->GetUserInteractions();

    for (const auto& FieldPair : UserInteractions.Fields)
    {
        if (FieldPair.Key == FieldName)
        {
            for (const auto& AreaPair : FieldPair.Value.Areas)
            {
                for (const auto& SubjectGroupPair : AreaPair.Value.SubjectGroups)
                {
                    for (const auto& SubjectPair : SubjectGroupPair.Value.Subjects)
                    {
                        for (const auto& SectionPair : SubjectPair.Value.Sections)
                        {
                            for (const auto& TopicPair : SectionPair.Value.Topics)
                            {
                                for (const auto& SubtopicPair : TopicPair.Value.Subtopics)
                                {
                                    for (const auto& QuestionPair : SubtopicPair.Value.Questions)
                                    {
                                        TotalTimesAsked += QuestionPair.Value.TimesAsked;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            return TotalTimesAsked;
        }
    }

    return 0; // Return 0 if no field with the given name is found
}



int32 UAssessmentMetricsCalculator::CalculateTimesCorrectForSubtopicInteract(const FString& SubtopicName, UUserInteractionDataManager* UserInteractionDataManagerLocal)
{
    int32 TotalTimesCorrect = 0;

    const FUserInteractionData& UserInteractions = UserInteractionDataManagerLocal->GetUserInteractions();

    for (const auto& FieldPair : UserInteractions.Fields)
    {
        for (const auto& AreaPair : FieldPair.Value.Areas)
        {
            for (const auto& SubjectGroupPair : AreaPair.Value.SubjectGroups)
            {
                for (const auto& SubjectPair : SubjectGroupPair.Value.Subjects)
                {
                    for (const auto& SectionPair : SubjectPair.Value.Sections)
                    {
                        for (const auto& TopicPair : SectionPair.Value.Topics)
                        {
                            for (const auto& SubtopicPair : TopicPair.Value.Subtopics)
                            {
                                if (SubtopicPair.Key == SubtopicName)
                                {
                                    for (const auto& QuestionPair : SubtopicPair.Value.Questions)
                                    {
                                        TotalTimesCorrect += QuestionPair.Value.TimesCorrect;
                                    }
                                    return TotalTimesCorrect;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 0; // Return 0 if no subtopic with the given name is found
}


int32 UAssessmentMetricsCalculator::CalculateTimesCorrectForTopicInteract(const FString& TopicName, UUserInteractionDataManager* UserInteractionDataManagerLocal)
{
    int32 TotalTimesCorrect = 0;

    const FUserInteractionData& UserInteractions = UserInteractionDataManagerLocal->GetUserInteractions();

    for (const auto& FieldPair : UserInteractions.Fields)
    {
        for (const auto& AreaPair : FieldPair.Value.Areas)
        {
            for (const auto& SubjectGroupPair : AreaPair.Value.SubjectGroups)
            {
                for (const auto& SubjectPair : SubjectGroupPair.Value.Subjects)
                {
                    for (const auto& SectionPair : SubjectPair.Value.Sections)
                    {
                        for (const auto& TopicPair : SectionPair.Value.Topics)
                        {
                            if (TopicPair.Key == TopicName)
                            {
                                for (const auto& SubtopicPair : TopicPair.Value.Subtopics)
                                {
                                    for (const auto& QuestionPair : SubtopicPair.Value.Questions)
                                    {
                                        TotalTimesCorrect += QuestionPair.Value.TimesCorrect;
                                    }
                                }
                                return TotalTimesCorrect;
                            }
                        }
                    }
                }
            }
        }
    }

    return 0; // Return 0 if no topic with the given name is found
}


int32 UAssessmentMetricsCalculator::CalculateTimesCorrectForSectionInteract(const FString& SectionName, UUserInteractionDataManager* UserInteractionDataManagerLocal)
{
    int32 TotalTimesCorrect = 0;

    const FUserInteractionData& UserInteractions = UserInteractionDataManagerLocal->GetUserInteractions();

    for (const auto& FieldPair : UserInteractions.Fields)
    {
        for (const auto& AreaPair : FieldPair.Value.Areas)
        {
            for (const auto& SubjectGroupPair : AreaPair.Value.SubjectGroups)
            {
                for (const auto& SubjectPair : SubjectGroupPair.Value.Subjects)
                {
                    for (const auto& SectionPair : SubjectPair.Value.Sections)
                    {
                        if (SectionPair.Key == SectionName)
                        {
                            for (const auto& TopicPair : SectionPair.Value.Topics)
                            {
                                for (const auto& SubtopicPair : TopicPair.Value.Subtopics)
                                {
                                    for (const auto& QuestionPair : SubtopicPair.Value.Questions)
                                    {
                                        TotalTimesCorrect += QuestionPair.Value.TimesCorrect;
                                    }
                                }
                            }
                            return TotalTimesCorrect;
                        }
                    }
                }
            }
        }
    }

    return 0; // Return 0 if no section with the given name is found
}

int32 UAssessmentMetricsCalculator::CalculateTimesCorrectForSubjectInteract(const FString& SubjectName, UUserInteractionDataManager* UserInteractionDataManagerLocal)
{
    int32 TotalTimesCorrect = 0;

    const FUserInteractionData& UserInteractions = UserInteractionDataManagerLocal->GetUserInteractions();

    for (const auto& FieldPair : UserInteractions.Fields)
    {
        for (const auto& AreaPair : FieldPair.Value.Areas)
        {
            for (const auto& SubjectGroupPair : AreaPair.Value.SubjectGroups)
            {
                for (const auto& SubjectPair : SubjectGroupPair.Value.Subjects)
                {
                    if (SubjectPair.Key == SubjectName)
                    {
                        for (const auto& SectionPair : SubjectPair.Value.Sections)
                        {
                            for (const auto& TopicPair : SectionPair.Value.Topics)
                            {
                                for (const auto& SubtopicPair : TopicPair.Value.Subtopics)
                                {
                                    for (const auto& QuestionPair : SubtopicPair.Value.Questions)
                                    {
                                        TotalTimesCorrect += QuestionPair.Value.TimesCorrect;
                                    }
                                }
                            }
                        }
                        return TotalTimesCorrect;
                    }
                }
            }
        }
    }

    return 0; // Return 0 if no subject with the given name is found
}

int32 UAssessmentMetricsCalculator::CalculateTimesCorrectForSubjectGroupInteract(const FString& SubjectGroupName, UUserInteractionDataManager* UserInteractionDataManagerLocal)
{
    int32 TotalTimesCorrect = 0;

    const FUserInteractionData& UserInteractions = UserInteractionDataManagerLocal->GetUserInteractions();

    for (const auto& FieldPair : UserInteractions.Fields)
    {
        for (const auto& AreaPair : FieldPair.Value.Areas)
        {
            for (const auto& SubjectGroupPair : AreaPair.Value.SubjectGroups)
            {
                if (SubjectGroupPair.Key == SubjectGroupName)
                {
                    for (const auto& SubjectPair : SubjectGroupPair.Value.Subjects)
                    {
                        for (const auto& SectionPair : SubjectPair.Value.Sections)
                        {
                            for (const auto& TopicPair : SectionPair.Value.Topics)
                            {
                                for (const auto& SubtopicPair : TopicPair.Value.Subtopics)
                                {
                                    for (const auto& QuestionPair : SubtopicPair.Value.Questions)
                                    {
                                        TotalTimesCorrect += QuestionPair.Value.TimesCorrect;
                                    }
                                }
                            }
                        }
                    }
                    return TotalTimesCorrect;
                }
            }
        }
    }

    return 0; // Return 0 if no subject group with the given name is found
}

int32 UAssessmentMetricsCalculator::CalculateTimesCorrectForAreaInteract(const FString& AreaName, UUserInteractionDataManager* UserInteractionDataManagerLocal)
{
    int32 TotalTimesCorrect = 0;

    const FUserInteractionData& UserInteractions = UserInteractionDataManagerLocal->GetUserInteractions();

    for (const auto& FieldPair : UserInteractions.Fields)
    {
        for (const auto& AreaPair : FieldPair.Value.Areas)
        {
            if (AreaPair.Key == AreaName)
            {
                for (const auto& SubjectGroupPair : AreaPair.Value.SubjectGroups)
                {
                    for (const auto& SubjectPair : SubjectGroupPair.Value.Subjects)
                    {
                        for (const auto& SectionPair : SubjectPair.Value.Sections)
                        {
                            for (const auto& TopicPair : SectionPair.Value.Topics)
                            {
                                for (const auto& SubtopicPair : TopicPair.Value.Subtopics)
                                {
                                    for (const auto& QuestionPair : SubtopicPair.Value.Questions)
                                    {
                                        TotalTimesCorrect += QuestionPair.Value.TimesCorrect;
                                    }
                                }
                            }
                        }
                    }
                }
                return TotalTimesCorrect;
            }
        }
    }

    return 0; // Return 0 if no area with the given name is found
}

int32 UAssessmentMetricsCalculator::CalculateTimesCorrectForFieldInteract(const FString& FieldName, UUserInteractionDataManager* UserInteractionDataManagerLocal)
{
    int32 TotalTimesCorrect = 0;

    const FUserInteractionData& UserInteractions = UserInteractionDataManagerLocal->GetUserInteractions();

    for (const auto& FieldPair : UserInteractions.Fields)
    {
        if (FieldPair.Key == FieldName)
        {
            for (const auto& AreaPair : FieldPair.Value.Areas)
            {
                for (const auto& SubjectGroupPair : AreaPair.Value.SubjectGroups)
                {
                    for (const auto& SubjectPair : SubjectGroupPair.Value.Subjects)
                    {
                        for (const auto& SectionPair : SubjectPair.Value.Sections)
                        {
                            for (const auto& TopicPair : SectionPair.Value.Topics)
                            {
                                for (const auto& SubtopicPair : TopicPair.Value.Subtopics)
                                {
                                    for (const auto& QuestionPair : SubtopicPair.Value.Questions)
                                    {
                                        TotalTimesCorrect += QuestionPair.Value.TimesCorrect;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            return TotalTimesCorrect;
        }
    }

    return 0; // Return 0 if no field with the given name is found
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


int32 UAssessmentMetricsCalculator::CalculateTimesCorrectForSubtopicIR(const FString& SubtopicTitle, const TArray<FFieldStruct>& FieldDataArray)
{
    for (const FFieldStruct& Field : FieldDataArray)
    {
        for (const FAreaStruct& Area : Field.Areas)
        {
            for (const FSubjectGroupStruct& SubjectGroup : Area.SubjectGroups)
            {
                for (const FSubjectStruct& Subject : SubjectGroup.Subjects)
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


FTest UAssessmentMetricsCalculator::UpdateAnswerStatus(int32 FieldIndex, int32 AreaIndex, int32 SubjectGroupIndex, int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText, TArray<FFieldStruct>& FieldDataArray)
{
    if (!FieldDataArray.IsValidIndex(FieldIndex)) return FTest();
    FFieldStruct& SelectedField = FieldDataArray[FieldIndex];
    FString FieldName = SelectedField.FieldName;


    if (!SelectedField.Areas.IsValidIndex(AreaIndex)) return FTest();
    FAreaStruct& SelectedArea = SelectedField.Areas[AreaIndex];
    FString AreaName = SelectedArea.AreaName;

    if (!SelectedArea.SubjectGroups.IsValidIndex(SubjectGroupIndex)) return FTest();
    FSubjectGroupStruct& SelectedSubjectGroup = SelectedArea.SubjectGroups[SubjectGroupIndex];
    FString SubjectGroupName = SelectedSubjectGroup.SubjectGroupName;

    if (!SelectedSubjectGroup.Subjects.IsValidIndex(SubjectIndex)) return FTest();
    FSubjectStruct& SelectedSubject = SelectedSubjectGroup.Subjects[SubjectIndex];
    FString SubjectName = SelectedSubject.SubjectName;

    if (!SelectedSubject.SubjectDetailsArray.IsValidIndex(SectionIndex)) return FTest();
    FSectionStruct& SelectedSection = SelectedSubject.SubjectDetailsArray[SectionIndex];
    FString SectionName = SelectedSection.SectionName;

    if (!SelectedSection.Topics.IsValidIndex(TopicIndex)) return FTest();
    FTopic& SelectedTopic = SelectedSection.Topics[TopicIndex];
    FString TopicName = SelectedTopic.Title;

    if (!SelectedTopic.Subtopics.IsValidIndex(SubtopicIndex)) return FTest();
    FSubtopic& SelectedSubtopic = SelectedTopic.Subtopics[SubtopicIndex];
    FString SubtopicName = SelectedSubtopic.Title;

    for (FTest& Question : SelectedSubtopic.Questions)
    {
        if (Question.Question == QuestionText)
        {
            Question.TimesTested++;
            if (SubmittedAnswer == Question.CorrectAnswer)
            {
                Question.TimesCorrect++;
            }

            // Here we update the QuestionInteractionData
            UserInteractionDataManager->UpdateQuestionInteractionData(FieldName, AreaName, SubjectGroupName, SubjectName, SectionName, TopicName, SubtopicName, QuestionText, SubmittedAnswer == Question.CorrectAnswer);

            return Question;
        }
    }
    return FTest(); // Return an empty FTest if no question with the given text is found
}





//int32 UAssessmentMetricsCalculator::GetTimesTestedForQuestion(int32 FieldIndex, int32 AreaIndex, int32 SubjectGroupIndex, int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText, TArray<FFieldStruct>& FieldDataArray)
//{
//    if (!FieldDataArray.IsValidIndex(FieldIndex)) return -1;
//    FFieldStruct& SelectedField = FieldDataArray[FieldIndex];
//    if (!SelectedField.Areas.IsValidIndex(AreaIndex)) return -1;
//    FAreaStruct& SelectedArea = SelectedField.Areas[AreaIndex];
//    if (!SelectedArea.SubjectGroups.IsValidIndex(SubjectGroupIndex)) return -1;
//    FSubjectGroupStruct& SelectedSubjectGroup = SelectedArea.SubjectGroups[SubjectGroupIndex];
//    if (!SelectedSubjectGroup.Subjects.IsValidIndex(SubjectIndex)) return -1;
//    FSubjectStruct& SelectedSubject = SelectedSubjectGroup.Subjects[SubjectIndex];
//    if (!SelectedSubject.SubjectDetailsArray.IsValidIndex(SectionIndex)) return -1;
//    FSectionStruct& SelectedSection = SelectedSubject.SubjectDetailsArray[SectionIndex];
//    if (!SelectedSection.Topics.IsValidIndex(TopicIndex)) return -1;
//    FTopic& SelectedTopic = SelectedSection.Topics[TopicIndex];
//    if (!SelectedTopic.Subtopics.IsValidIndex(SubtopicIndex)) return -1;
//    FSubtopic& SelectedSubtopic = SelectedTopic.Subtopics[SubtopicIndex];
//    for (FTest& Question : SelectedSubtopic.Questions)
//    {
//        if (Question.Question == QuestionText)
//        {
//            return Question.TimesTested;
//        }
//    }
//    return -1; // Return -1 if no question with the given text is found
//}

int32 UAssessmentMetricsCalculator::GetTimesTestedForQuestion(int32 FieldIndex, int32 AreaIndex, int32 SubjectGroupIndex, int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText, TArray<FFieldStruct>& FieldDataArray)
{
    if (!FieldDataArray.IsValidIndex(FieldIndex)) return -1;
    FFieldStruct& SelectedField = FieldDataArray[FieldIndex];
    FString FieldNameStr = SelectedField.FieldName;

    if (!SelectedField.Areas.IsValidIndex(AreaIndex)) return -1;
    FAreaStruct& SelectedArea = SelectedField.Areas[AreaIndex];
    FString AreaNameStr = SelectedArea.AreaName;

    if (!SelectedArea.SubjectGroups.IsValidIndex(SubjectGroupIndex)) return -1;
    FSubjectGroupStruct& SelectedSubjectGroup = SelectedArea.SubjectGroups[SubjectGroupIndex];
    FString SubjectGroupNameStr = SelectedSubjectGroup.SubjectGroupName;

    if (!SelectedSubjectGroup.Subjects.IsValidIndex(SubjectIndex)) return -1;
    FSubjectStruct& SelectedSubject = SelectedSubjectGroup.Subjects[SubjectIndex];
    FString SubjectNameStr = SelectedSubject.SubjectName;

    if (!SelectedSubject.SubjectDetailsArray.IsValidIndex(SectionIndex)) return -1;
    FSectionStruct& SelectedSection = SelectedSubject.SubjectDetailsArray[SectionIndex];
    FString SectionNameStr = SelectedSection.SectionName;

    if (!SelectedSection.Topics.IsValidIndex(TopicIndex)) return -1;
    FTopic& SelectedTopic = SelectedSection.Topics[TopicIndex];
    FString TopicNameStr = SelectedTopic.Title;

    if (!SelectedTopic.Subtopics.IsValidIndex(SubtopicIndex)) return -1;
    FSubtopic& SelectedSubtopic = SelectedTopic.Subtopics[SubtopicIndex];
    FString SubtopicNameStr = SelectedSubtopic.Title;

    FFieldInteractionData* FieldInteractionData = UserInteractionDataManager->UserInteractions.Fields.Find(FieldNameStr);
    if (FieldInteractionData)
    {
        FAreaInteractionData* AreaInteractionData = FieldInteractionData->Areas.Find(AreaNameStr);
        if (AreaInteractionData)
        {
            FSubjectGroupInteractionData* SubjectGroupInteractionData = AreaInteractionData->SubjectGroups.Find(SubjectGroupNameStr);
            if (SubjectGroupInteractionData)
            {
                FSubjectInteractionData* SubjectInteractionData = SubjectGroupInteractionData->Subjects.Find(SubjectNameStr);
                if (SubjectInteractionData)
                {
                    FSectionInteractionData* SectionInteractionData = SubjectInteractionData->Sections.Find(SectionNameStr);
                    if (SectionInteractionData)
                    {
                        FTopicInteractionData* TopicInteractionData = SectionInteractionData->Topics.Find(TopicNameStr);
                        if (TopicInteractionData)
                        {
                            FSubtopicInteractionData* SubtopicInteractionData = TopicInteractionData->Subtopics.Find(SubtopicNameStr);
                            if (SubtopicInteractionData)
                            {
                                FQuestionInteractionData* QuestionInteractionData = SubtopicInteractionData->Questions.Find(QuestionText);
                                if (QuestionInteractionData)
                                {
                                    UE_LOG(LogTemp, Warning, TEXT("Getting TimesTested count for question: %s. Count: %d"), *QuestionText, QuestionInteractionData->TimesAsked);

                                    return QuestionInteractionData->TimesAsked;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return -1; // Return -1 if no question with the given text is found
}



//int32 UAssessmentMetricsCalculator::GetTimesCorrectForQuestion(int32 FieldIndex, int32 AreaIndex, int32 SubjectGroupIndex, int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText, TArray<FFieldStruct>& FieldDataArray)
//{
//    if (!FieldDataArray.IsValidIndex(FieldIndex)) return -1;
//    FFieldStruct& SelectedField = FieldDataArray[FieldIndex];
//    if (!SelectedField.Areas.IsValidIndex(AreaIndex)) return -1;
//    FAreaStruct& SelectedArea = SelectedField.Areas[AreaIndex];
//    if (!SelectedArea.SubjectGroups.IsValidIndex(SubjectGroupIndex)) return -1;
//    FSubjectGroupStruct& SelectedSubjectGroup = SelectedArea.SubjectGroups[SubjectGroupIndex];
//    if (!SelectedSubjectGroup.Subjects.IsValidIndex(SubjectIndex)) return -1;
//    FSubjectStruct& SelectedSubject = SelectedSubjectGroup.Subjects[SubjectIndex];
//    if (!SelectedSubject.SubjectDetailsArray.IsValidIndex(SectionIndex)) return -1;
//    FSectionStruct& SelectedSection = SelectedSubject.SubjectDetailsArray[SectionIndex];
//    if (!SelectedSection.Topics.IsValidIndex(TopicIndex)) return -1;
//    FTopic& SelectedTopic = SelectedSection.Topics[TopicIndex];
//    if (!SelectedTopic.Subtopics.IsValidIndex(SubtopicIndex)) return -1;
//    FSubtopic& SelectedSubtopic = SelectedTopic.Subtopics[SubtopicIndex];
//    for (FTest& Question : SelectedSubtopic.Questions)
//    {
//        if (Question.Question == QuestionText)
//        {
//            return Question.TimesCorrect;
//        }
//    }
//    return -1; // Return -1 if no question with the given text is found
//}

int32 UAssessmentMetricsCalculator::GetTimesCorrectForQuestion(int32 FieldIndex, int32 AreaIndex, int32 SubjectGroupIndex, int32 SubjectIndex, int32 SectionIndex, int32 TopicIndex, int32 SubtopicIndex, const FString& QuestionText, TArray<FFieldStruct>& FieldDataArray)
{
    if (!FieldDataArray.IsValidIndex(FieldIndex)) return -1;
    FFieldStruct& SelectedField = FieldDataArray[FieldIndex];
    FString FieldNameStr = SelectedField.FieldName;

    if (!SelectedField.Areas.IsValidIndex(AreaIndex)) return -1;
    FAreaStruct& SelectedArea = SelectedField.Areas[AreaIndex];
    FString AreaNameStr = SelectedArea.AreaName;

    if (!SelectedArea.SubjectGroups.IsValidIndex(SubjectGroupIndex)) return -1;
    FSubjectGroupStruct& SelectedSubjectGroup = SelectedArea.SubjectGroups[SubjectGroupIndex];
    FString SubjectGroupNameStr = SelectedSubjectGroup.SubjectGroupName;

    if (!SelectedSubjectGroup.Subjects.IsValidIndex(SubjectIndex)) return -1;
    FSubjectStruct& SelectedSubject = SelectedSubjectGroup.Subjects[SubjectIndex];
    FString SubjectNameStr = SelectedSubject.SubjectName;

    if (!SelectedSubject.SubjectDetailsArray.IsValidIndex(SectionIndex)) return -1;
    FSectionStruct& SelectedSection = SelectedSubject.SubjectDetailsArray[SectionIndex];
    FString SectionNameStr = SelectedSection.SectionName;

    if (!SelectedSection.Topics.IsValidIndex(TopicIndex)) return -1;
    FTopic& SelectedTopic = SelectedSection.Topics[TopicIndex];
    FString TopicNameStr = SelectedTopic.Title;

    if (!SelectedTopic.Subtopics.IsValidIndex(SubtopicIndex)) return -1;
    FSubtopic& SelectedSubtopic = SelectedTopic.Subtopics[SubtopicIndex];
    FString SubtopicNameStr = SelectedSubtopic.Title;

    FFieldInteractionData* FieldInteractionData = UserInteractionDataManager->UserInteractions.Fields.Find(FieldNameStr);
    if (FieldInteractionData)
    {
        FAreaInteractionData* AreaInteractionData = FieldInteractionData->Areas.Find(AreaNameStr);
        if (AreaInteractionData)
        {
            FSubjectGroupInteractionData* SubjectGroupInteractionData = AreaInteractionData->SubjectGroups.Find(SubjectGroupNameStr);
            if (SubjectGroupInteractionData)
            {
                FSubjectInteractionData* SubjectInteractionData = SubjectGroupInteractionData->Subjects.Find(SubjectNameStr);
                if (SubjectInteractionData)
                {
                    FSectionInteractionData* SectionInteractionData = SubjectInteractionData->Sections.Find(SectionNameStr);
                    if (SectionInteractionData)
                    {
                        FTopicInteractionData* TopicInteractionData = SectionInteractionData->Topics.Find(TopicNameStr);
                        if (TopicInteractionData)
                        {
                            FSubtopicInteractionData* SubtopicInteractionData = TopicInteractionData->Subtopics.Find(SubtopicNameStr);
                            if (SubtopicInteractionData)
                            {
                                FQuestionInteractionData* QuestionInteractionData = SubtopicInteractionData->Questions.Find(QuestionText);
                                if (QuestionInteractionData)
                                {
                                    UE_LOG(LogTemp, Warning, TEXT("Getting TimesCorrect count for question: %s. Count: %d"), *QuestionText, QuestionInteractionData->TimesCorrect);

                                    return QuestionInteractionData->TimesCorrect;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return -1; // Return -1 if no question with the given text is found
}


void UAssessmentMetricsCalculator::SetUserInteractionDataManager(UUserInteractionDataManager* manager)
{
    UserInteractionDataManager = manager;
}


