import static java.lang.System.nanoTime;
import java.util.ArrayList;
import java.util.Scanner;
import java.io.FileReader;
import java.io.IOException;
import static java.lang.System.out;
import java.io.BufferedReader;
import java.util.Arrays;

/**
 * Write a description of class LerFichVendas here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class LerFichVendas{
	public static ArrayList<String> readLinesArrayWithScanner(String ficheiro){
		ArrayList<String> linhas = new ArrayList<>();
		Scanner scanFile = null;
		try {
			scanFile = new Scanner(new FileReader(ficheiro));
			scanFile.useDelimiter("\n\r");
			while(scanFile.hasNext())
				linhas.add(scanFile.nextLine());
		}
		catch(IOException ioExc){
			out.println(ioExc.getMessage()); return null;
		}
		finally {
			if(scanFile != null) scanFile.close();
		}
		return linhas;
	}

	public static ArrayList<String> readLinesWithBuff(String fich) {
		ArrayList<String> linhas = new ArrayList<>();
		BufferedReader inStream = null; 
		String linha = null;
		try {
			inStream = new BufferedReader(new FileReader(fich));
			while( (linha = inStream.readLine()) != null ){
				linhas.add(linha);
			}
		}
		catch(IOException e){
			out.println(e.getMessage()); return null; 
		};
		return linhas;
	}

	public static void main(String[] args){
		String ficheiro = "Vendas_1M.txt";
		long timeinit = nanoTime();
		ArrayList<String> linhas = readLinesWithBuff(ficheiro);
		long timefin = nanoTime();
		long diff = timefin - timeinit;
		StringBuilder sb = new StringBuilder();
		sb.append(diff);
		sb.append("nº de linhas:");
		sb.append(linhas.size());
		System.out.println(sb.toString());
		

	}
}
