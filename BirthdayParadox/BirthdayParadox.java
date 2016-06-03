/* Group Name :: Juggernaut
 * Group ID :: 65
 * Problem Statement :: Birthday Paradox Problem - In a set of n random people, will two of them share the same birthday
 * Assumptions :: Non-leap years consisting of 365 days are considered. A person's birthday does not fall on 29th February.
 */
import java.io.*;
import java.util.*;
public class BirthdayParadox
{
	public static int randExp(int np) //Conducts random experiment of matching birthdays of 'np' people 
	{
		int[] birthday = new int[365]; //Array for storing birthday where indices 0-364 are for days 1-365 in a non-leap year
		   //Value 0 at Birthday[index] indicates that no person has birthday on that particular day 'index'
		   //Value 1 at Birthday[index] indicates that a person has birthday on that particular day 'index'

		int matchRes=0; //Result for matching birthday
		Random rand = new Random();
		
		for(int i = 0; i < np; i++)
		{
			int randDay = rand.nextInt((365 - 1) + 1) + 1; //Generates random day for 'i' person's birthday
			if(birthday[randDay - 1] == 1)
			{
				matchRes = 1; //Successful result for matching birthdays
				break; //Match occurs as a person's birthday already falls on day 'randDay'
			}
			else
				birthday[randDay - 1] = 1;			
		} //for ends here
		return matchRes;
	} //randExp ends here
	
	public static void main(String[] args) throws IOException
	{
		BufferedReader br = new BufferedReader( new InputStreamReader( System.in ) );
		
		int numPeople; //Number of people
		int numTrials; //Number of trials for conducting random experiment of matching birthdays of 'numPeople' people
		while(true)
		{
			System.out.println("Enter the number of people :: ");
			numPeople = Integer.parseInt( br.readLine() );
			
			if(numPeople>=2)
				break;
			else
				System.out.println("Number of people should be atleast greater than or equal to 2 !! ");
		}
		
		while(true)
		{		
			System.out.println("Enter the number of trials for conducting random experiment of matching birthdays :: ");
			numTrials = Integer.parseInt( br.readLine() );
			
			if(numTrials>0)
				break;
			else
				System.out.println("Number of trials should be greater than 0 !! ");
		}		
		System.out.println("");
		
		int numMatch = 0; //Number of trials in which successful match was found
		double probActualMatch; //Probability of successful trials in which a match was found
		
		System.out.println("List of Trial Numbers in which successful match was not found :: ");
		
		for(int i = 1; i <= numTrials; i++)
		{
			int res = randExp(numPeople); //Conduct random experiment for trial number 'i'
			if(res==1)
				numMatch += res; //Increment number of successful matches
			else
				System.out.print(i+"  ");			
		} //for ends here
		System.out.println("\n");
		
		probActualMatch = (double)numMatch/(double)numTrials;
		
		int numComp=(numPeople*(numPeople-1))/2; //Number of comparisons
		System.out.println("Number of comparisons where one person's birthday is being compared against someone else's = C("+numPeople+",2) = "+numComp);
		
		System.out.print("Probability of two people having different birthdays = 364/365 = ");
		System.out.printf("%.4f",((364.0/365.0)*100.0));
		System.out.println("%");
		
		System.out.print("Probability of all "+numComp+" pairs having different birthdays = (364/365)^"+numComp+" = ");
		double probDiff=Math.pow((364.0/365.0),numComp); //Probability of all pairs having different birthdays
		System.out.printf("%.4f",probDiff*100.0);
		System.out.println("%");
		
		System.out.print("Probability of having a match (Theoretical) = 1 - ");
		System.out.printf("%.4f",probDiff*100.0);
		System.out.print("% = ");
		System.out.printf("%.4f",(1-probDiff)*100.0);
		System.out.println("%\n");
		
		
		System.out.print("Probability of Actual Match (Experimental) = "+numMatch+"/"+numTrials+" = ");
		System.out.printf("%.2f",(probActualMatch*100.0));
		System.out.println("%\n");
		
		System.out.println("Birthday Paradox holds true and is valid and two people in a set of n random people can share the same birthday ");

	} //main ends here

} //class ends here
