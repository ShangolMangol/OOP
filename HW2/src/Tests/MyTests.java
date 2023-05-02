package Tests;

import OOP2.Provided.*;
import OOP2.Solution.FaceOOPImpl;
import OOP2.Solution.PersonImpl;
import OOP2.Solution.StatusImpl;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;
import org.omg.CORBA.FREE_MEM;

import java.sql.Array;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;

public class MyTests
{

    private static <T> int getSize(Iterable<T> iterable)
    {
        int size = 0;

        for(T a : iterable)
        {
            size++;
        }

        return size;
    }
    private FaceOOP mFace;

    @Before
    public void setUp()
    {
        mFace = new FaceOOPImpl();
    }

    @Test
    public void statusBasicTest()
    {
        Person person = new PersonImpl(1, "name");
        int id = 1;
        String content = "asd";
        Status status = new StatusImpl(person, content, id);
        Assert.assertEquals("asd", status.getContent());
        Assert.assertEquals(Integer.valueOf(1), status.getId());
        Assert.assertEquals(status.getPublisher(), new PersonImpl(1, "name"));

        Assert.assertEquals(status.getLikesCount(), Integer.valueOf(0));
        status.like(person);
        Assert.assertEquals(status.getLikesCount(), Integer.valueOf(1));
        status.like(new PersonImpl(2, "asdf"));
        Assert.assertEquals(status.getLikesCount(), Integer.valueOf(2));
        status.like(person);
        status.like(new PersonImpl(2, "asdf"));
        Assert.assertEquals(status.getLikesCount(), Integer.valueOf(2));

        status.unlike(new PersonImpl(3, "adasd"));
        Assert.assertEquals(status.getLikesCount(), Integer.valueOf(2));
        status.unlike(person);
        Assert.assertEquals(status.getLikesCount(), Integer.valueOf(1));
        status.unlike(person);
        Assert.assertEquals(status.getLikesCount(), Integer.valueOf(1));
        status.unlike(new PersonImpl(2, "asdf"));
        Assert.assertEquals(status.getLikesCount(), Integer.valueOf(0));
        status.unlike(new PersonImpl(2, "asdf"));
        Assert.assertEquals(status.getLikesCount(), Integer.valueOf(0));
        status.unlike(person);
        Assert.assertEquals(status.getLikesCount(), Integer.valueOf(0));

        Status statusA = new StatusImpl(person, "as", id);
        Status statusB = new StatusImpl(new PersonImpl(1, "asd"), "as", id);
        Status statusC = new StatusImpl(new PersonImpl(2, "asd"), "as", id);
        Status statusD = new StatusImpl(new PersonImpl(1, "asd"), "as", 42);
        Status statusE = new StatusImpl(new PersonImpl(3, "asd"), "as", 42);

        Assert.assertEquals(status, statusA);
        Assert.assertEquals(status, statusB);
        Assert.assertNotEquals(status, statusC);
        Assert.assertNotEquals(status, statusD);
        Assert.assertNotEquals(status, statusE);

        Assert.assertNotEquals(status, null);
        Assert.assertNotEquals(status, "asda");
        Assert.assertNotEquals(status, 3);
    }

    @Test
    public void personBasicTest() throws SamePersonException, ConnectionAlreadyExistException
    {
        PersonImpl person = new PersonImpl(554, "asd");
        Assert.assertEquals(person.getName(), "asd");
        Assert.assertEquals(person.getId(), Integer.valueOf(554));


        Assert.assertEquals(person.getFriends().size(), 0);
        Assert.assertThrows(SamePersonException.class, () -> person.addFriend(person));
        Assert.assertEquals(person.getFriends().size(), 0);
        Assert.assertThrows(SamePersonException.class, () -> person.addFriend(new PersonImpl(554, "asda")));
        Assert.assertEquals(person.getFriends().size(), 0);

        PersonImpl friend = new PersonImpl(324, "ef");
        person.addFriend(friend);
        Assert.assertEquals(person.getFriends().size(), 1);
        Assert.assertTrue(person.getFriends().contains(friend));
        Assert.assertThrows(ConnectionAlreadyExistException.class, () -> person.addFriend(friend));
        Assert.assertThrows(ConnectionAlreadyExistException.class, () -> person.addFriend(new PersonImpl(324, "asd")));
        person.addFriend(new PersonImpl(123, "add"));
        Assert.assertEquals(person.getFriends().size(), 2);
        Assert.assertTrue(person.getFriends().contains(new PersonImpl(123,"asd")));


        Assert.assertEquals(friend, new PersonImpl(324, "asdasd"));
        Assert.assertEquals(new PersonImpl(324, "asdasd"), new PersonImpl(324, "asdasd"));
        Assert.assertNotEquals(friend, new PersonImpl(344, "asdasd"));
        Assert.assertNotEquals(friend, null);
        Assert.assertNotEquals(friend, "asda");
        Assert.assertNotEquals(friend, 3);


        Assert.assertTrue(friend.compareTo(new PersonImpl(500, "asdasd")) < 0);
        Assert.assertTrue(friend.compareTo(new PersonImpl(100, "asdasd")) > 0);
        Assert.assertTrue(friend.compareTo(new PersonImpl(324, "asdasd")) == 0);

        Assert.assertEquals(getSize(person.getStatusesRecent()), 0);
        Assert.assertEquals(getSize(person.getStatusesPopular()), 0);
        person.postStatus("aa");
        Assert.assertEquals(getSize(person.getStatusesRecent()), 1);
        Assert.assertEquals(getSize(person.getStatusesPopular()), 1);
        person.postStatus("bb");
        Assert.assertEquals(getSize(person.getStatusesRecent()), 2);
        Assert.assertEquals(getSize(person.getStatusesPopular()), 2);
        person.postStatus("cc");
        Assert.assertEquals(getSize(person.getStatusesRecent()), 3);
        Assert.assertEquals(getSize(person.getStatusesPopular()), 3);

        Iterator<Status> iter;
        Status temp;

        iter = person.getStatusesRecent().iterator();
        temp = iter.next();
        Assert.assertEquals(temp.getId(), Integer.valueOf(2));
        Assert.assertEquals(temp.getContent(), "cc");
        temp = iter.next();
        Assert.assertEquals(temp.getId(), Integer.valueOf(1));
        Assert.assertEquals(temp.getContent(), "bb");
        temp = iter.next();
        Assert.assertEquals(temp.getId(), Integer.valueOf(0));
        Assert.assertEquals(temp.getContent(), "aa");
        Assert.assertFalse(iter.hasNext());


        iter = person.getStatusesPopular().iterator();
        temp = iter.next();
        Assert.assertEquals(temp.getId(), Integer.valueOf(2));
        Assert.assertEquals(temp.getContent(), "cc");
        temp = iter.next();
        Assert.assertEquals(temp.getId(), Integer.valueOf(1));
        Assert.assertEquals(temp.getContent(), "bb");
        temp = iter.next();
        Assert.assertEquals(temp.getId(), Integer.valueOf(0));
        Assert.assertEquals(temp.getContent(), "aa");
        Assert.assertFalse(iter.hasNext());

        temp.like(new PersonImpl(123,"asd"));

        iter = person.getStatusesRecent().iterator();
        temp = iter.next();
        Assert.assertEquals(temp.getId(), Integer.valueOf(2));
        Assert.assertEquals(temp.getContent(), "cc");
        temp = iter.next();
        Assert.assertEquals(temp.getId(), Integer.valueOf(1));
        Assert.assertEquals(temp.getContent(), "bb");
        temp = iter.next();
        Assert.assertEquals(temp.getId(), Integer.valueOf(0));
        Assert.assertEquals(temp.getContent(), "aa");
        Assert.assertFalse(iter.hasNext());


        iter = person.getStatusesPopular().iterator();
        temp = iter.next();
        Assert.assertEquals(temp.getId(), Integer.valueOf(0));
        Assert.assertEquals(temp.getContent(), "aa");
        temp = iter.next();
        Assert.assertEquals(temp.getId(), Integer.valueOf(2));
        Assert.assertEquals(temp.getContent(), "cc");
        temp = iter.next();
        Assert.assertEquals(temp.getId(), Integer.valueOf(1));
        Assert.assertEquals(temp.getContent(), "bb");
        Assert.assertFalse(iter.hasNext());



        person.postStatus("dd");
        Assert.assertEquals(getSize(person.getStatusesRecent()), 4);
        Assert.assertEquals(getSize(person.getStatusesPopular()), 4);

        iter = person.getStatusesRecent().iterator();
        temp = iter.next();
        Assert.assertEquals(temp.getId(), Integer.valueOf(3));
        Assert.assertEquals(temp.getContent(), "dd");
        temp = iter.next();
        Assert.assertEquals(temp.getId(), Integer.valueOf(2));
        Assert.assertEquals(temp.getContent(), "cc");
        temp = iter.next();
        Assert.assertEquals(temp.getId(), Integer.valueOf(1));
        Assert.assertEquals(temp.getContent(), "bb");
        temp = iter.next();
        Assert.assertEquals(temp.getId(), Integer.valueOf(0));
        Assert.assertEquals(temp.getContent(), "aa");
        Assert.assertFalse(iter.hasNext());


        iter = person.getStatusesPopular().iterator();
        temp = iter.next();
        Assert.assertEquals(temp.getId(), Integer.valueOf(0));
        Assert.assertEquals(temp.getContent(), "aa");
        temp = iter.next();
        Assert.assertEquals(temp.getId(), Integer.valueOf(3));
        Assert.assertEquals(temp.getContent(), "dd");
        temp = iter.next();
        Assert.assertEquals(temp.getId(), Integer.valueOf(2));
        Assert.assertEquals(temp.getContent(), "cc");
        temp = iter.next();
        Assert.assertEquals(temp.getId(), Integer.valueOf(1));
        Assert.assertEquals(temp.getContent(), "bb");
        Assert.assertFalse(iter.hasNext());

    }

    @Test
    public void faceOopTest() throws PersonAlreadyInSystemException,
            PersonNotInSystemException, SamePersonException, ConnectionAlreadyExistException
    {
        Person luke = new PersonImpl(12, "luke");
        Person leia =new PersonImpl(30, "leia");
        Person han = new PersonImpl(45, "han");
        Person lando = new PersonImpl(23, "lando");
        Person anakin = new PersonImpl(57, "anakin");
        try
        {
            mFace.joinFaceOOP(12, "luke");
            mFace.joinFaceOOP(30, "leia");
            mFace.joinFaceOOP(45, "han");
            mFace.joinFaceOOP(23, "lando");
            mFace.joinFaceOOP(57, "anakin");
        } catch (PersonAlreadyInSystemException e)
        {
            Assert.fail();
        }
        try
        {
            mFace.joinFaceOOP(12, "rey");
        } catch (PersonAlreadyInSystemException e)
        {
            Assert.assertTrue(true);
        }

        Assert.assertEquals(5, mFace.size());

        try
        {
            Assert.assertEquals(luke, mFace.getUser(12));
            Assert.assertEquals(leia, mFace.getUser(30));
            Assert.assertEquals(han, mFace.getUser(45));
            Assert.assertEquals(lando, mFace.getUser(23));
            Assert.assertEquals(anakin, mFace.getUser(57));
        } catch (PersonNotInSystemException e)
        {
            Assert.fail();
        }

        try
        {
            mFace.getUser(123);
        } catch (PersonNotInSystemException e)
        {
            Assert.assertTrue(true);
        }


        luke = mFace.getUser(12);
        leia = mFace.getUser(30);
        han = mFace.getUser(45);
        lando = mFace.getUser(23);
        anakin = mFace.getUser(57);

        mFace.addFriendship(luke, leia);
        mFace.addFriendship(luke, han);
        mFace.addFriendship(han, leia);
        mFace.addFriendship(leia, lando);
        mFace.addFriendship(leia, anakin);
        try
        {
            mFace.addFriendship(luke, leia);
        } catch (ConnectionAlreadyExistException e)
        {
            Assert.assertTrue(true);
        }
        try
        {
            Person rey = new PersonImpl(13, "rey");
            mFace.addFriendship(luke, rey);
        } catch (PersonNotInSystemException e)
        {
            Assert.assertTrue(true);
        }
        try
        {
            mFace.addFriendship(luke, luke);
        } catch (SamePersonException e)
        {
            Assert.assertTrue(true);
        }

        try
        {
            mFace.addFriendship(luke, han);
        } catch (ConnectionAlreadyExistException e)
        {
            Assert.assertTrue(true);
        }

        try
        {
            mFace.addFriendship(han, luke);
        } catch (ConnectionAlreadyExistException e)
        {
            Assert.assertTrue(true);
        }

        mFace.getUser(12).postStatus("greetings");
        mFace.getUser(30).postStatus("you are my only hope");
        mFace.getUser(45).postStatus("pokey religions and ancient weapons are no match for a good blaster at your side");
        mFace.getUser(23).postStatus("wooo hooooo");
        mFace.getUser(57).postStatus("i hate sand");
        mFace.getUser(57).postStatus("this is where the fun begins");
        mFace.getUser(57).postStatus("i've brought peace, freedom, justice, and security to my new empire");


        ArrayList<Status> posts= new ArrayList<>((Collection) mFace.getUser(57).getStatusesRecent());
        posts.get(1).like(luke);
        posts.get(1).like(han);
        posts= new ArrayList<>((Collection) mFace.getUser(57).getStatusesPopular());
        Assert.assertEquals(new StatusImpl(anakin, "this is where the fun begins", posts.get(0).getId()),posts.get(0));


        Iterator<Status> iterator = mFace.getFeedByRecent(mFace.getUser(12));
        Assert.assertTrue(iterator.hasNext());
        Assert.assertEquals("you are my only hope", iterator.next().getContent());
        System.out.println(iterator.next().getContent());
        Assert.assertFalse(iterator.hasNext());


    }
}
