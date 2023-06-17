package solution;

import org.junit.ComparisonFailure;
import provided.*;

import java.lang.reflect.*;

public class StoryTesterImpl implements StoryTester
{
    private static final String SPACE = " ";
    private static final String NEW_LINE = "\n";

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

        private String getRawLine()
        {
            return mRawLine;
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
            String annoText = null;

            if(getType() == TestType.Given)
            {
                Given given = method.getAnnotation(Given.class);
                annoText = given != null ? given.value() : null;
            }
            else if(getType() == TestType.When)
            {
                When given = method.getAnnotation(When.class);
                annoText = given != null ? given.value() : null;
            }
            else if(getType() == TestType.Then)
            {
                Then then = method.getAnnotation(Then.class);
                annoText = then != null ? then.value() : null;
            }

            if(annoText == null)
            {
                return false;
            }

            //remove last word
            int lastSpaceIndex = annoText.lastIndexOf(SPACE);
            String newSentence = annoText.substring(0, lastSpaceIndex);
            return newSentence.equals(getContent());
        }
    }

    public static Method getTestMethod(Class<?> testClass, TestLine testLine)
    {

        for(Method method : testClass.getDeclaredMethods())
        {
            if(testLine.isCorrectMethod(method))
            {
                return method;
            }
        }

        if(testClass != Object.class)
        {
            return getTestMethod(testClass.getSuperclass(), testLine);
        }

        return null;
    }

    public static void invokeTestMethod(Object testInstance, TestLine testLine, Method testMethod)
            throws InvocationTargetException, IllegalAccessException
    {
        testMethod.setAccessible(true);
        String methodArg = testLine.getValue();
        //check if Integer
        if(testMethod.getParameterTypes()[0] == Integer.class)
            testMethod.invoke(testInstance, Integer.parseInt(testLine.getValue()));
        else
            testMethod.invoke(testInstance, methodArg);
    }

    public static Object sudoNew(Class<?> objClass)
            throws NoSuchMethodException, InvocationTargetException, InstantiationException, IllegalAccessException
    {
        Class<?> enclosing = objClass.getEnclosingClass();
        if(enclosing != null)
        {
            Object enclosingValue = sudoNew(enclosing);
            Constructor<?> ctor = objClass.getDeclaredConstructor(enclosing);
            ctor.setAccessible(true);
            return ctor.newInstance(enclosingValue);
        }
        else
        {
            Constructor<?> defaultConstructor = objClass.getDeclaredConstructor();
            defaultConstructor.setAccessible(true);
            return defaultConstructor.newInstance();
        }
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

        Object backupObj = sudoNew(objClass);

        for (Field field : objClass.getDeclaredFields())
        {
            field.setAccessible(true);

            Object fieldValue = field.get(obj);
            Object newValue;
            Class<?> fieldClass = fieldValue.getClass();
            Constructor<?> copyConstructor = safeGetCopyConstructor(fieldClass);

            if(fieldValue instanceof Cloneable)
            {
                Method clone = fieldClass.getMethod("clone");
                clone.setAccessible(true);
                newValue = clone.invoke(fieldValue);
            }
            else if(copyConstructor != null)
            {
                copyConstructor.setAccessible(true);
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
        Object testInstance = sudoNew(testClass);
        String[] sentences = story.split(NEW_LINE);
        StoryTestExceptionImpl testException = null;
        Object backupInstance = null;
        boolean firstWhen = true;
        for (String sentence: sentences)
        {
            TestLine testLine = new TestLine(sentence);
            Method testMethod = getTestMethod(testClass, testLine);
            if(testMethod == null)
                testLine.throwNotFoundType();

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
            catch (InvocationTargetException invocationTargetException)
            {
                Throwable target = invocationTargetException.getTargetException();
                if(!(target instanceof ComparisonFailure))
                    throw invocationTargetException;
                
                ComparisonFailure comparisonFailure = (ComparisonFailure) target;
                testInstance = backupInstance;
                if(testException == null)
                {
                    testException = new StoryTestExceptionImpl(testLine.getRawLine(), comparisonFailure.getExpected(), comparisonFailure.getActual());
                }
                testException.incrementFailCount();
            }
        }
        if(testException != null)
            throw testException;
    }


    private Class<?> findClassWithGiven(TestLine testLine, Class<?> testClass)
    {
        if(getTestMethod(testClass, testLine) != null)
        {
            return testClass;
        }
        for(Class<?> declaredClass : testClass.getDeclaredClasses())
        {
            if(declaredClass.isInterface())
                continue;

            if(getTestMethod(declaredClass, testLine) != null)
            {
                return declaredClass;
            }
            else if(testClass != Object.class)
            {
                Class<?> result = findClassWithGiven(testLine, declaredClass);
                if(result != null)
                    return result;
            }
        }

        return null;
    }

    @Override
    public void testOnNestedClasses(String story, Class<?> testClass) throws Exception
    {
        String firstLine = story.split(NEW_LINE)[0];
        TestLine testLine = new TestLine(firstLine);
        Class<?> newTestClass = findClassWithGiven(testLine, testClass);
        testOnInheritanceTree(story, newTestClass);
    }
}
