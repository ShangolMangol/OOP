package Tests;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;

import OOP2.Solution.PersonImpl;
import junit.framework.Assert;

import org.junit.Test;

import OOP2.Provided.FaceOOP;
import OOP2.Provided.Person;
import OOP2.Provided.PersonAlreadyInSystemException;
import OOP2.Provided.Status;
import OOP2.Solution.FaceOOPImpl;

public class Example {
	@Test
	public void ExampleTest()
	{
		FaceOOP fo = new FaceOOPImpl();
		Person pA = null, pB = null;
		try {
			pA = fo.joinFaceOOP(100, "Anne");
			pB = fo.joinFaceOOP(300, "Ben");
		} catch (PersonAlreadyInSystemException e) {
			Assert.fail();
		}
		Status statA = pA.postStatus("Going to Thailand!!");
		Status statB = pA.postStatus("Love you all!");
		
		statA.like(pB);
		Assert.assertTrue(statA.getLikesCount() == 1);
		
		Iterator<Status> stIt = pA.getStatusesRecent().iterator();
		Assert.assertEquals(stIt.next(), statB);
		Assert.assertEquals(stIt.next(), statA);

		stIt = pA.getStatusesPopular().iterator();
		Assert.assertEquals(stIt.next(), statA);
		Assert.assertEquals(stIt.next(), statB);
		
		try {
			fo.addFriendship(pA, pB);
		} catch (Exception e) {
			Assert.fail();
		}
		
		try {
			Assert.assertTrue(fo.rank(pA, pB) == 1);
		} catch (Exception e) {
			Assert.fail();
		} 
	}

	@Test
	public void ArrayListTest()
	{
		ArrayList<Person> persons = new ArrayList<>();
		persons.add(new PersonImpl(1, "aa"));
		Assert.assertTrue( persons.contains(new PersonImpl(1, "aa")));

		persons.remove(new PersonImpl(2, "aa"));

	}


}
