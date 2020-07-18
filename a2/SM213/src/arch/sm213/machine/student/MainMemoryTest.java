package arch.sm213.machine.student;

import machine.AbstractMainMemory;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static junit.framework.TestCase.fail;
import static org.junit.jupiter.api.Assertions.*;

public class MainMemoryTest {
    MainMemory testMem;
    @BeforeEach
    public void setup(){
        testMem = new MainMemory(32);
    }

    @Test
    public void testIsAccessAligned(){
        assertTrue(testMem.isAccessAligned(20,4));
        assertFalse(testMem.isAccessAligned(23,2));
    }

    @Test
    public void testSetWithOutException(){
        int a = 35;
        int b = 72;
        byte[] value = new byte[4];
        value[0] = (byte)a;
        value[1] = (byte)b;
        try {
            testMem.set(0, value);
        }catch (AbstractMainMemory.InvalidAddressException e){
            fail("should not throw exception here");
        }
    }

    @Test
    public void testSetWithException(){
        int a = 35;
        int b = 72;
        byte[] value = new byte[4];
        value[0] = (byte)a;
        value[1] = (byte)b;
        try {
            testMem.set(testMem.length() + 1, value);
            fail("should throw exception here");
        }catch (AbstractMainMemory.InvalidAddressException e){
        }
      }

    @Test
    public void testGetWithException(){
        byte a = 0x70;
        int b = 0x35;
        byte[] value = new byte[4];
        value[0] = (byte)a;
        value[1] = (byte)b;
        try {
            testMem.set(20, value);
        }catch (AbstractMainMemory.InvalidAddressException e){
            fail("should not throw exception here");
        }

        try {
            byte[] bytes = testMem.get(20, value.length);
            assertEquals(value[0] , bytes[0]);
        }catch(AbstractMainMemory.InvalidAddressException e){
            fail("should not throw exception here");
        }
    }

    @Test
    public void testBytesToInteger(){

    }


}
