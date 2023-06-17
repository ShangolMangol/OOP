package ourTests;

import org.junit.Assert;
import org.junit.Test;
import solution.StoryTestExceptionImpl;
import solution.StoryTesterImpl;

import java.lang.reflect.InvocationTargetException;

public class TestBackup
{
    static class Cloned implements Cloneable
    {
        public String value;

        public Cloned(String value)
        {
            this.value = value;
        }

        @Override
        public Object clone() throws CloneNotSupportedException
        {
            Object cloned = super.clone();
            ((Cloned) cloned).value = "Cloned";
            return cloned;
        }

        public Cloned(Cloned other)
        {
            value = "copied";
        }
    }

    static class Copied
    {
        public String value;

        public Copied(String value)
        {
            this.value = value;
        }

        public Copied(Copied other)
        {
            value = "copied";
        }
    }

    static class Regular
    {
        public Regular(String value)
        {
            this.value = value;
        }

        public String value;
    }

    static class NoConstructor
    {
        public String value;
    }

    static class ToBackupAll
    {
        ToBackupAll()
        {

        }

        Cloned a;
        Cloned b;
        Copied c;
        Copied d;
        Regular e;
        Regular f;
        NoConstructor g;
    }

    static class ToBackupNon
    {
        ToBackupNon()
        {

        }

        int a;
    }

    @Test
    public void runBackup() throws InvocationTargetException, InstantiationException, IllegalAccessException, NoSuchMethodException
    {
        NoConstructor noConstructor = new NoConstructor();
        noConstructor.value = "init";
        ToBackupAll all = new ToBackupAll();
        all.a = new Cloned("init");
        all.b = new Cloned("init");
        all.c = new Copied("init");
        all.d = new Copied("init");
        all.e = new Regular("init");
        all.f = new Regular("init");
        all.g = noConstructor;

        ToBackupAll backupAll = (ToBackupAll) StoryTesterImpl.createBackup(all);
        Assert.assertEquals(backupAll.a.value, "Cloned");
        Assert.assertEquals(backupAll.b.value, "Cloned");
        Assert.assertEquals(backupAll.c.value, "copied");
        Assert.assertEquals(backupAll.d.value, "copied");
        Assert.assertEquals(backupAll.e.value, "init");
        Assert.assertEquals(backupAll.f.value, "init");
        Assert.assertEquals(backupAll.g.value, "init");

        ToBackupNon non = new ToBackupNon();
        non.a = 10;
        ToBackupNon backupNon = (ToBackupNon) StoryTesterImpl.createBackup(non);
        Assert.assertEquals(backupNon.a, 10);
    }
}
