package arch.sm213.machine.student;

import machine.AbstractMainMemory;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.Assert.*;
import static org.junit.jupiter.api.Assertions.assertFalse;


class MainMemoryTest {
    private MainMemory testMainMemory;

    @BeforeEach
    void runBefore() {
        testMainMemory = new MainMemory(32);
    }

    @org.junit.jupiter.api.Test
    void testIsAccessAligned() {

        assertTrue(testMainMemory.isAccessAligned(4, 4));
        assertTrue(testMainMemory.isAccessAligned(8, 4));
        assertTrue(testMainMemory.isAccessAligned(6, 3));
        assertFalse(testMainMemory.isAccessAligned(4, 8));
        assertFalse(testMainMemory.isAccessAligned(4,3));
    }

    @Test
    void testBytesToInteger() {
        byte[] testByte1 = {0x01, 0x02, 0x03, 0x04};
        int expectedInt1 = 0x1020304;
        byte[] testByte2 = {(byte) 0xfe, (byte) 0xdc, (byte) 0xba, (byte) 0x98};
        int expectedInt2 = 0xfedcba98;

        assertEquals(testMainMemory.bytesToInteger(testByte1[0], testByte1[1], testByte1[2], testByte1[3]), expectedInt1);
        assertEquals(testMainMemory.bytesToInteger(testByte2[0], testByte2[1], testByte2[2], testByte2[3]), expectedInt2);
    }

    @Test
    void testIntegerToBytes() {
        byte[] testByte1 = {0x01, 0x02, 0x03, 0x04};
        int expectedInt1 = 0x1020304;
        byte[] testByte2 = {(byte) 0xfe, (byte) 0xdc, (byte) 0xba, (byte) 0x98};
        int expectedInt2 = 0xfedcba98;

        assertArrayEquals(testMainMemory.integerToBytes(expectedInt1), testByte1);
        assertArrayEquals(testMainMemory.integerToBytes(expectedInt2), testByte2);
    }

    @Test
    void testGetSet() {
        byte[] testByte1 = {0x01, 0x02, 0x03, 0x04};
        byte[] expectedByte1 = {0x01, 0x02};
        byte[] testByte2 = {(byte) 0xfe, (byte) 0xdc, (byte) 0xba, (byte) 0x98};
        byte[] expectedByte2 = {(byte) 0xba, (byte) 0x98};
        byte[] expectedByte3 = {0x00, 0x00, 0x00, 0x00, 0x00};
        byte[] expectedByte4 = {(byte) 0x01, (byte) 0x02, (byte) 0x03, (byte) 0x04, 0x00, 0x00};

        try{
        testMainMemory.set(4,testByte1);
        testMainMemory.set(24,testByte2);
        assertArrayEquals(testMainMemory.get(4, 2), expectedByte1);
        assertArrayEquals(testMainMemory.get(26, 2), expectedByte2);
        assertArrayEquals(testMainMemory.get(8,5), expectedByte3);
        testMainMemory.set(24, testByte1);
        assertArrayEquals(testMainMemory.get(24, 6), expectedByte4);
        } catch (AbstractMainMemory.InvalidAddressException e){
            fail("should not catch exception.");
        }
    }


    @Test
    void testSetWithExceptionNegative(){
        byte[] testByte1 = {0x01, 0x02, 0x03, 0x04};
        try{
            testMainMemory.set(-1,testByte1);
            fail("should catch exception.");
        } catch (AbstractMainMemory.InvalidAddressException e){
        }
    }

    @Test
    void testSetWithExceptionEqualsAddress(){
        byte[] testByte1 = {0x01, 0x02, 0x03, 0x04};
        try{
            testMainMemory.set(29,testByte1);
            fail("should catch exception.");
        } catch (AbstractMainMemory.InvalidAddressException e){
        }
    }

    @Test
    void testSetWithExceptionBiggerThanAddress(){
        byte[] testByte1 = {0x01, 0x02, 0x03, 0x04};
        try{
            testMainMemory.set(30,testByte1);
            fail("should catch exception.");
        } catch (AbstractMainMemory.InvalidAddressException e){
        }
    }

    @Test
    void testGetWithExceptionNegative(){
        try{
            testMainMemory.get(-4,2);
            fail("should catch exception.");
        } catch (AbstractMainMemory.InvalidAddressException e){
        }
    }

    @Test
    void testGetWithExceptionEqualsAddress(){
        try{
            testMainMemory.get(32, 2);
            fail("should catch exception.");
        } catch (AbstractMainMemory.InvalidAddressException e){
        }
    }

    @Test
    void testGetWithExceptionBiggerThanAddress(){
        try{
            testMainMemory.get(35, 5);
            fail("should catch exception.");
        } catch (AbstractMainMemory.InvalidAddressException e){
        }
    }

    @Test
    void testMemLength(){
        assertEquals(32,testMainMemory.length());
    }

}