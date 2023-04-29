package OOP2.Provided;

import java.util.Collection;


/**
 * Each instance of the Person class has an id and a name, and holds collections of the statuses
 * posted by this Person and of this Person's friends. The id is unique for every person.
 * 
 * A Person can post a new status and let others view their statuses.  A Person can also befriend
 * other Persons.
 */
public interface Person extends Comparable<Person> {
	/**
	 * @return the person's id
	 */
	public Integer getId();

	/**
	 * @return the person's name
	 */
	public String getName();

	/**
	 * Adds a new status to the person's collection of statuses.
	 * 
	 * @param content - the status content
	 * @return the new status
	 */
	public Status postStatus(String content);
	
	/**
	 * Add a connection between this Person and another.
	 * 
	 * @param p the Person to be added as a friend
	 *	 
	 * @throws SamePersonException if p is the same person as the current instance.
	 * @throws ConnectionAlreadyExistException if p is already a friend of this person
	 */
	public void addFriend(Person p) 
			throws SamePersonException, ConnectionAlreadyExistException;
	
	/**
	 * @return collection of this person's friends
	 */
	public Collection<Person> getFriends();
	
	/**
	 * @return an iterable collection of all the person's statuses. 
	 * 		The statuses are sorted by chronological descending order 
	 * 		(LIFO order - last posted are first returned by iterator).
	 */
	public Iterable<Status> getStatusesRecent();

	/**
	 * @return an iterable collection of all the person's statuses. 
	 * 		The statuses are sorted by descending order of number of likes.
	 */
	public Iterable<Status> getStatusesPopular();
	


}
