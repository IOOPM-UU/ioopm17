import java.io.IOException;

class ParserDriver{
    public static void main(String[] args){
        Parser p = new Parser();

        System.out.println("Welcome to the parser!");
        System.out.print("Please enter an expression: ");

        try{
            double result = p.expression();
            System.out.println("result: " + result);
        }catch(SyntaxErrorException e){
            System.out.print("Syntax Error: ");
            System.out.println(e.getMessage());
        }catch(IOException e){
            System.err.println("IO Exception!");
        }
    }
}