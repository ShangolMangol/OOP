package solution;

import org.junit.ComparisonFailure;
import provided.*;

import java.lang.annotation.Annotation;
import java.lang.reflect.*;

public class StoryTesterImpl implements StoryTester
{
    private static final String SPACE = " ";
    private static final String NEWLINE = "\n";

    enum TestType
    {
        Given,
        When,
        Then
    }

    public static class TestLine
    {
        private static final int TYPE_INDEX = 0;
        private final String mRawLine;
        private final TestType mType;
        private final String mContent;
        private final String mValue;



        TestLine(String rawLine)
        {
            mRawLine = rawLine;
            mType = parseType();
            mContent = parseContent();
            mValue = parseValue();
        }

        private TestType parseType()
        {
            String type = mRawLine.split(SPACE)[TYPE_INDEX];
            switch (type)
            {
                case "Given": return TestType.Given;
                case "Then": return TestType.Then;
                case "When": return TestType.When;
            }
            throw new RuntimeException("enum value not found, should never happen");
        }

        TestType getType()
        {
            return mType;
        }

        private String parseContent()
        {
            int start = mRawLine.indexOf(SPACE) + 1;
            int end = mRawLine.lastIndexOf(SPACE);
            return mRawLine.substring(start, end);
        }

        String getContent()
        {
            return mContent;
        }

        private String parseValue()
        {
            String [] words = mRawLine.split(SPACE);
            return words[words.length - 1];
        }

        String getValue()
        {
            return mValue;
        }

        boolean isWhenType()
        {
            return getType() == TestType.When;
        }

        public void throwNotFoundType() throws WordNotFoundException
        {
            if(getType() == TestType.Given)
            {
                throw new GivenNotFoundException();
            }
            else if(getType() == TestType.When)
            {
                throw new WhenNotFoundException();
            }
            else if(getType() == TestType.Then)
            {
                throw new ThenNotFoundException();
            }

            throw new RuntimeException("enum value not found, should never happen");
        }

        public boolean isCorrectMethod(Method method)
        {
            String annoText;
            if(getType() == TestType.Given)
            {
                annoText = method.getAnnotation(Given.class).value();
            }
            else if(getType() == TestType.When)
            {
                annoText = method.getAnnotation(When.class).value();
            }
            else if(getType() == TestType.Then)
            {
                annoText = method.getAnnotation(Then.class).value();
            }
            else
            {
                return false;
            }

            //remove last word
            int lastSpaceIndex = annoText.lastIndexOf(SPACE);
            String newSentence = annoText.substring(0, lastSpaceIndex);
            return newSentence.equals(getContent());
        }
    }




    public static Method getTestMethod(Class<?> testClass, TestLine testLine) throws WordNotFoundException
    {
        for(Method method : testClass.getDeclaredMethods())
        {
            if(testLine.isCorrectMethod(method))
            {
                return method;
            }
        }

        testLine.throwNotFoundType();
        throw new RuntimeException("enum value not found, should never happen");
    }

    public static void invokeTestMethod(Object testInstance, TestLine testLine, Method testMethod)
            throws InvocationTargetException, IllegalAccessException
    {
        String methodArg = testLine.getValue();
        //check if Integer
        if(testMethod.getParameterTypes()[0] == Integer.class)
            testMethod.invoke(testInstance, Integer.parseInt(testLine.getValue()));
        else
            testMethod.invoke(testInstance, methodArg);
    }


    public static Constructor<?> safeGetCopyConstructor(Class<?> type)
    {
        try
        {
            return type.getConstructor(type);
        }
        catch (NoSuchMethodException e)
        {
            return null;
        }
    }

    public static Object createBackup(Object obj)
            throws InstantiationException, IllegalAccessException, NoSuchMethodException, InvocationTargetException
    {
        Class<?> objClass = obj.getClass();

        Object backupObj = objClass.newInstance();

        for (Field field : objClass.getDeclaredFields())
        {
            Object fieldValue = field.get(obj);
            Object newValue;
            Class<?> fieldClass = fieldValue.getClass();
            Constructor<?> copyConstructor = safeGetCopyConstructor(fieldClass);

            if(fieldValue instanceof Cloneable)
            {
                Method clone = fieldClass.getMethod("clone");
                newValue = clone.invoke(fieldValue);
            }
            else if(copyConstructor != null)
            {
                newValue = copyConstructor.newInstance(fieldValue);
            }
            else
            {
                newValue = fieldValue;
            }

            field.set(backupObj, newValue);
        }
        return backupObj;
    }



    @Override
    public void testOnInheritanceTree(String story, Class<?> testClass) throws Exception
    {
        //create instance of testClass by finding the default constructor
        Object testInstance = testClass.newInstance();
        String[] sentences = story.split(NEWLINE);

        Object backupInstance;
        boolean firstWhen = true;
        for (String sentence: sentences)
        {
            TestLine testLine = new TestLine(sentence);
            Method testMethod = getTestMethod(testClass, testLine);

            if(testLine.isWhenType() && firstWhen)
            {
                backupInstance = createBackup(testInstance);
                firstWhen = false;
            }
            else if(!testLine.isWhenType())
            {
                firstWhen = true;
            }

            try
            {
                invokeTestMethod(testInstance, testLine, testMethod);
            }
            catch (ComparisonFailure comparisonFailure)
            {

            }
        }
        /*
        for each line in story
            get line type
            get line data
            get line arg value


            try
                find methode in all inheritance that has the annotate type and the data description
            throw error

            if first "when" backup
            if the method is "Then", catch the assert failure
                restore on failure


         check if there is any errors and throw the correct exception
         */





    }

    @Override
    public void testOnNestedClasses(String story, Class<?> testClass) throws Exception
    {

    }
}
