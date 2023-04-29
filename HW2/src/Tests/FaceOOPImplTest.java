package OOP2.Tests;

import OOP2.Provided.*;
import OOP2.Solution.FaceOOPImpl;

import org.junit.Assert;

import org.junit.Test;

import java.util.Iterator;

import static org.junit.Assert.*;

public class FaceOOPImplTest {

    private FaceOOP obj = new FaceOOPImpl();
    Status s1;
    Status s2;
    Status s3;
    Status s32;
    Status s22;
    Status s4;
    Status s42;
    Status s33;


    public void joinFaceOOP() {
        try {
            obj.joinFaceOOP(318269495, "david");
            obj.joinFaceOOP(209404409, "gal");
        }
        catch (PersonAlreadyInSystemException e)
        {
            Assert.fail("WTF?! person already exists");
        }
        try {
            obj.joinFaceOOP(318269485, "david");
            obj.joinFaceOOP(318269495, "igal");
        }
        catch (PersonAlreadyInSystemException e)
        {
            Assert.assertTrue(true);
        }
    }


    public void size() {
        assertEquals(3, obj.size());
        try {
            obj.joinFaceOOP(1, "user1");
            obj.joinFaceOOP(2, "user2");
            obj.joinFaceOOP(3, "user3");
            obj.joinFaceOOP(4, "user4");
            obj.joinFaceOOP(5, "user5");
            obj.joinFaceOOP(6, "user6");
            obj.joinFaceOOP(7, "user7");
            obj.joinFaceOOP(8, "user8");
            obj.joinFaceOOP(9, "user9");
        }
        catch (PersonAlreadyInSystemException e)
        {
            Assert.fail("WTF?! person already exists");
        }
        assertEquals(12, obj.size());
    }


    public void getUser() {
        try {
            assertEquals("david", obj.getUser(318269485).getName());
            assertEquals("david", obj.getUser(318269495).getName());
            assertEquals("gal", obj.getUser(209404409).getName());
            assertEquals("gal", obj.getUser(209404409).getName());
            assertEquals("david", obj.getUser(318269495).getName());
            assertEquals("gal", obj.getUser(209404409).getName());
            assertEquals("david", obj.getUser(318269495).getName());
            assertEquals("gal", obj.getUser(209404409).getName());
        }
        catch (PersonNotInSystemException e)
        {
            Assert.fail();
        }

        try {
            assertEquals("gal", obj.getUser(209404405).getName());
        }
        catch (PersonNotInSystemException ignored)
        {

        }
        try {
            assertNotEquals("gAl", obj.getUser(209404409).getName());
        }
        catch (PersonNotInSystemException ignored)
        {

        }
    }


    public void addFriendship() {

        try {
            obj.addFriendship(obj.getUser(318269499), obj.getUser(209404409));
        }
        catch (PersonNotInSystemException ignored)
        {

        }
        catch (SamePersonException | ConnectionAlreadyExistException e)
        {
            Assert.fail();
        }

        try {
            obj.addFriendship(obj.getUser(318269495), obj.getUser(209404409));
        }
        catch (PersonNotInSystemException | SamePersonException | ConnectionAlreadyExistException e)
        {
            Assert.fail();
        }

        try {
            obj.addFriendship(obj.getUser(209404409), obj.getUser(318269499));
        }
        catch (PersonNotInSystemException ignored)
        {

        }

        catch (SamePersonException | ConnectionAlreadyExistException e)
        {
            Assert.fail();
        }

        try {
            obj.addFriendship(obj.getUser(209404409), obj.getUser(209404409));
        }
        catch (SamePersonException ignored)
        {

        }
        catch (PersonNotInSystemException | ConnectionAlreadyExistException e)
        {
            Assert.fail();
        }
        try {
            obj.addFriendship(obj.getUser(2), obj.getUser(3)); // 2 -> 3 4
            obj.addFriendship(obj.getUser(2), obj.getUser(4)); // 3 -> 2 5 8
            obj.addFriendship(obj.getUser(3), obj.getUser(5)); // 4 -> 2
            obj.addFriendship(obj.getUser(8), obj.getUser(3)); // 5 -> 3
            obj.addFriendship(obj.getUser(1), obj.getUser(7)); // 7 -1, 1 -> 7
            /*Friends:
             * 1: 7
             * 2: 3, 4
             * 3: 2, 5, 8
             * 4: 2
             * 5: 3
             * 6:
             * 7: 1
             * 8: 3
             * 9: */
        }
        catch (PersonNotInSystemException | SamePersonException | ConnectionAlreadyExistException e)
        {
            Assert.fail();
        }


        try {
            obj.addFriendship(obj.getUser(203404409), obj.getUser(203404409));
        }
        catch (PersonNotInSystemException ignored)
        {

        }
        catch (SamePersonException | ConnectionAlreadyExistException e)
        {
            Assert.fail();
        }

        try {
            obj.addFriendship(obj.getUser(318269495), obj.getUser(209404409));
        }
        catch (PersonNotInSystemException | SamePersonException e)
        {
            Assert.fail();
        }
        catch (ConnectionAlreadyExistException ignored)
        {

        }

        try {
            obj.addFriendship(obj.getUser(209404409), obj.getUser(318269495));
        }
        catch (PersonNotInSystemException | SamePersonException e)
        {
            Assert.fail();
        }
        catch (ConnectionAlreadyExistException ignored)
        {

        }


        try {
            obj.addFriendship(obj.getUser(209404409), obj.getUser(318269495));
        }
        catch (PersonNotInSystemException | SamePersonException e)
        {
            Assert.fail();
        }
        catch (ConnectionAlreadyExistException ignored)
        {

        }

        try {
            obj.addFriendship(obj.getUser(209404409), obj.getUser(318269495));
        }
        catch (PersonNotInSystemException | SamePersonException e)
        {
            Assert.fail();
        }
        catch (ConnectionAlreadyExistException ignored)
        {

        }
    }


    public void addPost()
    {
        try {
            assertFalse(obj.getFeedByRecent(obj.getUser(2)).hasNext());
        }
        catch(PersonNotInSystemException ignored)
        {

        }
        try {
            s1 = obj.getUser(1).postStatus("Rak bibi!");
            s2 = obj.getUser(2).postStatus("2");
            s3 = obj.getUser(3).postStatus("2");
            s32 = obj.getUser(3).postStatus("3");
            s22 = obj.getUser(2).postStatus("2");
            s4 = obj.getUser(4).postStatus("4");
            s42 = obj.getUser(4).postStatus("44");
            s33 = obj.getUser(3).postStatus("33");
        }
        /*Feeds:
        1:
        2: 33, 3, 2, 44, 4
        3: 2, 2
        4: 2, 2
        5: 33, 3, 2
        8: 33, 3, 2
        */

        catch (PersonNotInSystemException ignored){}

//        try {
//            assertNull(obj.getUser(1).postStatus(null));
//        }
//        catch (PersonNotInSystemException ignored){}
    }




    public void getFeedByRecent() {
        try {
            assertFalse(obj.getFeedByRecent(obj.getUser(318269495)).hasNext());
            assertFalse(obj.getFeedByRecent(obj.getUser(1)).hasNext());
        }
        catch(PersonNotInSystemException ignored)
        {

        }

        try {
            Iterator<Status> it = obj.getFeedByRecent(obj.getUser(2));
            assertEquals("33", it.next().getContent());
            assertEquals("3", it.next().getContent());
            assertEquals("2", it.next().getContent());
            assertEquals("44", it.next().getContent());
            assertEquals("4", it.next().getContent());


            it = obj.getFeedByRecent(obj.getUser(3));
            assertEquals("2", it.next().getContent());
            assertEquals("2", it.next().getContent());


            it = obj.getFeedByRecent(obj.getUser(4));
            assertEquals("2", it.next().getContent());
            assertEquals("2", it.next().getContent());


            it = obj.getFeedByRecent(obj.getUser(5));
            assertEquals("33", it.next().getContent());
            assertEquals("3", it.next().getContent());
            assertEquals("2", it.next().getContent());


            it = obj.getFeedByRecent(obj.getUser(8));
            assertEquals("33", it.next().getContent());
            assertEquals("3", it.next().getContent());
            assertEquals("2", it.next().getContent());

            it = obj.getFeedByRecent(obj.getUser(4));
            assertEquals("2", it.next().getContent());
            assertEquals("2", it.next().getContent());
            assertFalse(it.hasNext());
        }
        catch(PersonNotInSystemException ignored)
        {

        }


    }


    public void like()
    {
        try {
            s2.like(obj.getUser(3));
            s2.like(obj.getUser(1));
            s3.like(obj.getUser(3));
            s32.like(obj.getUser(1));
            s32.like(obj.getUser(2));
            s32.like(obj.getUser(3));
            s32.like(obj.getUser(1));
            s32.like(obj.getUser(1));
            s4.like(obj.getUser(5));
            s42.like(obj.getUser(1));
            s42.like(obj.getUser(8));
            s42.like(obj.getUser(7));
            s42.like(obj.getUser(9));
            s42.like(obj.getUser(4));
            s42.like(obj.getUser(2));
            s2.like(obj.getUser(2));
            s33.like(obj.getUser(9));
        }
        catch (PersonNotInSystemException e)
        {
            Assert.fail();
        }
    }

    /*Likes:
     * s1 = 0
     * s2 = 3
     * s3 = 1
     * s32 = 3
     * s22 = 0
     * s4 = 1
     * s42 = 6
     * s33 = 1*/


    public void likeCount()
    {
        assertEquals(0, (int)s1.getLikesCount());
        assertEquals(3, (int)s2.getLikesCount());
        assertEquals(1, (int)s3.getLikesCount());
        assertEquals(3, (int)s32.getLikesCount());
        assertEquals(0, (int)s22.getLikesCount());
        assertEquals(1, (int)s4.getLikesCount());
        assertEquals(6, (int)s42.getLikesCount());
        assertEquals(1, (int)s33.getLikesCount());
    }


    public void getFeedByPopular() {
        /*Friends:
         * 1: 7
         * 2: 3, 4
         * 3: 2, 5, 8
         * 4: 2
         * 5: 3
         * 6:
         * 7: 1
         * 8: 3
         * 9: */

        /*Feeds:
        1:
        2: 3, 33, 2, 44, 4
        3: 2, 2
        4: 2, 2
        5: 3, 3, 2
        8: 3, 3, 2
        */
        try {
            assertFalse(obj.getFeedByPopular(obj.getUser(318269495)).hasNext());
            assertFalse(obj.getFeedByPopular(obj.getUser(1)).hasNext());
        }
        catch(PersonNotInSystemException ignored)
        {

        }

        try {
            Iterator<Status> it = obj.getFeedByPopular(obj.getUser(2));
            assertEquals("3", it.next().getContent());
            assertEquals("33", it.next().getContent());
            assertEquals("2", it.next().getContent());
            assertEquals("44", it.next().getContent());
            assertEquals("4", it.next().getContent());


            it = obj.getFeedByPopular(obj.getUser(3));
            assertEquals("2", it.next().getContent());
            assertEquals("2", it.next().getContent());


            it = obj.getFeedByPopular(obj.getUser(4));
            assertEquals("2", it.next().getContent());
            assertEquals("2", it.next().getContent());


            it = obj.getFeedByPopular(obj.getUser(5));
            assertEquals("3", it.next().getContent());
            assertEquals("33", it.next().getContent());
            assertEquals("2", it.next().getContent());


            it = obj.getFeedByPopular(obj.getUser(8));
            assertEquals("3", it.next().getContent());
            assertEquals("33", it.next().getContent());
            assertEquals("2", it.next().getContent());

            it = obj.getFeedByPopular(obj.getUser(4));
            assertEquals("2", it.next().getContent());
            assertEquals("2", it.next().getContent());
            assertFalse(it.hasNext());
        }
        catch(PersonNotInSystemException ignored)
        {

        }

    }


    public void unlike()
    {
        try {
            s2.unlike(obj.getUser(3));
            s2.unlike(obj.getUser(1));
            s3.unlike(obj.getUser(3));
            s32.unlike(obj.getUser(1));
            s32.unlike(obj.getUser(2));
            s32.unlike(obj.getUser(3));
            s32.unlike(obj.getUser(1));
            s32.unlike(obj.getUser(1));
            s4.unlike(obj.getUser(5));
            s42.unlike(obj.getUser(1));
            s42.unlike(obj.getUser(8));
            s42.unlike(obj.getUser(7));
            s42.unlike(obj.getUser(9));
            s42.unlike(obj.getUser(4));
            s42.unlike(obj.getUser(2));
            s2.unlike(obj.getUser(2));
            s33.unlike(obj.getUser(9));
        }
        catch (PersonNotInSystemException e)
        {
            Assert.fail();
        }

        assertEquals(0, (int)s1.getLikesCount());
        assertEquals(0, (int)s2.getLikesCount());
        assertEquals(0, (int)s3.getLikesCount());
        assertEquals(0, (int)s32.getLikesCount());
        assertEquals(0, (int)s22.getLikesCount());
        assertEquals(0, (int)s4.getLikesCount());
        assertEquals(0, (int)s42.getLikesCount());
        assertEquals(0, (int)s33.getLikesCount());
    }


    public void rank() {
        /*Friends:
         * 1: 7
         * 2: 3, 4
         * 3: 2, 5, 8
         * 4: 2
         * 5: 3
         * 6:
         * 7: 1
         * 8: 3
         * 9: */

        try {
            assertEquals(1, (int)obj.rank(obj.getUser(1), obj.getUser(7)));
            assertEquals(1, (int)obj.rank(obj.getUser(7), obj.getUser(1)));
            assertEquals(1, (int)obj.rank(obj.getUser(3), obj.getUser(2)));
            assertEquals(2, (int)obj.rank(obj.getUser(2), obj.getUser(5)));
            assertEquals(0, (int)obj.rank(obj.getUser(7), obj.getUser(7)));
            assertEquals(1, (int)obj.rank(obj.getUser(4), obj.getUser(2)));
            assertEquals(2, (int)obj.rank(obj.getUser(2), obj.getUser(8)));
            assertEquals(3, (int)obj.rank(obj.getUser(4), obj.getUser(8)));
            assertEquals(2, (int)obj.rank(obj.getUser(3), obj.getUser(4)));
            assertEquals(0, (int)obj.rank(obj.getUser(6), obj.getUser(6)));
            assertEquals(0, (int)obj.rank(obj.getUser(9), obj.getUser(9)));
        }
        catch (PersonNotInSystemException | ConnectionDoesNotExistException e)
        {
            Assert.fail();
        }

        //Test ConnectionDoesn'tExist
        try {
            obj.rank(obj.getUser(7), obj.getUser(9));
            obj.rank(obj.getUser(6), obj.getUser(3));
            obj.rank(obj.getUser(1), obj.getUser(4));
        }
        catch (PersonNotInSystemException e)
        {
            Assert.fail();
        }
        catch (ConnectionDoesNotExistException e)
        {
            assertTrue(true);
        }

        //Test person doesn't exist
        try {
            obj.rank(obj.getUser(2), obj.getUser(11));
        }
        catch (PersonNotInSystemException e)
        {
            assertTrue(true);
        }
        catch (ConnectionDoesNotExistException e)
        {
            Assert.fail();
        }

        //Test circles in graph
        //Create circle
        try {
            obj.addFriendship(obj.getUser(2), obj.getUser(1));
            obj.addFriendship(obj.getUser(7), obj.getUser(4));
            obj.addFriendship(obj.getUser(4), obj.getUser(8));
        }
        catch (PersonNotInSystemException | SamePersonException | ConnectionAlreadyExistException e)
        {
            Assert.fail();
        }

        try {
            assertEquals(1, (int)obj.rank(obj.getUser(1), obj.getUser(2)));
            assertEquals(2, (int)obj.rank(obj.getUser(7), obj.getUser(2)));
            assertEquals(1, (int)obj.rank(obj.getUser(1), obj.getUser(7)));
            assertEquals(1, (int)obj.rank(obj.getUser(7), obj.getUser(4)));
            assertEquals(1, (int)obj.rank(obj.getUser(4), obj.getUser(8)));
            assertEquals(2, (int)obj.rank(obj.getUser(8), obj.getUser(7)));
            assertEquals(1, (int)obj.rank(obj.getUser(3), obj.getUser(2)));
        }

        catch (PersonNotInSystemException | ConnectionDoesNotExistException e)
        {
            Assert.fail();
        }
    }

    public void iterator() {
         /*Feeds:
        1:
        2: 33, 3, 2, 44, 4
        3: 2, 2
        4: 2, 2
        5: 33, 3, 2
        8: 33, 3, 2
        */
        Person p;
        Status nr,np;
        StatusIterator recent, popular;
        for (Person person : obj) {
            p = person;
            try {
                recent = obj.getFeedByRecent(p);
                popular = obj.getFeedByPopular(p);
                while (recent.hasNext() && popular.hasNext()) {
                    nr = recent.next();
                    np = popular.next();
                    assertEquals(nr, np);
                }
            } catch (PersonNotInSystemException e) {
                Assert.fail();
            }
        }
    }

    @Test
    public void MasterTest()
    {
        this.joinFaceOOP();
        this.size();
        this.getUser();
        this.addFriendship();
        this.addPost();
        this.getFeedByRecent();
        this.like();
        this.likeCount();
        this.getFeedByPopular();
        this.unlike();
        this.iterator();
        this.rank();
    }
}