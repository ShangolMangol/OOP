package OOP2.Provided;

/**
 * Each instance of the Status class has a 'publisher' (The Person who posted the status),
 *  an id, and a String content. A status is defined by its publisher and id.
 * 
 * Statuses can be liked and unliked.
 */
public interface Status {

	/**
	 * @return the id of the status
	 */
	Integer getId();
	
	/**
	 * @return the person who posted this status
	 */
	Person getPublisher();
	
	/**
	 * @return the text content of the status
	 */
	String getContent();
	
	/**
	 * @param Person who is "liking" the status
	 */
	void like(Person p);
	
	/**
	 * @param Person who is "unliking" the status
	 */
	void unlike(Person p);
	
	/**
	 * @return the number of people who currently like the status.
	 */
	Integer getLikesCount();
}
