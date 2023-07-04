package solution;

import ourTests.TestBackup;
import provided.StoryTestException;

public class StoryTestExceptionImpl extends StoryTestException
{
    private String mGotSentence;
    private String mExpectedSentence;
    private String mTestResult;
    private int mFailCount;
    StoryTestExceptionImpl(String sentence, String expected, String result)
    {
        mGotSentence = sentence;
        mExpectedSentence = expected;
        mTestResult = result;
        mFailCount = 0;
    }


    @Override
    public String getSentance()
    {
        return mGotSentence;
    }

    @Override
    public String getStoryExpected()
    {
        return mExpectedSentence;
    }

    @Override
    public String getTestResult()
    {
        return mTestResult;
    }

    @Override
    public int getNumFail()
    {
        return mFailCount;
    }

    public void incrementFailCount()
    {
        mFailCount++;
    }

}
