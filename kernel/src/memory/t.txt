
mm_malloc.o:     file format elf32-i386


Disassembly of section .text:

00000000 <mm_malloc>:
   0:	55                   	push   %ebp
   1:	31 c0                	xor    %eax,%eax
   3:	89 e5                	mov    %esp,%ebp
   5:	57                   	push   %edi
   6:	56                   	push   %esi
   7:	53                   	push   %ebx
   8:	83 ec 3c             	sub    $0x3c,%esp
   b:	8b 5d 0c             	mov    0xc(%ebp),%ebx
   e:	85 db                	test   %ebx,%ebx
  10:	0f 8e 36 02 00 00    	jle    24c <mm_malloc+0x24c>
  16:	e8 fc ff ff ff       	call   17 <mm_malloc+0x17>
  1b:	89 c6                	mov    %eax,%esi
  1d:	e8 fc ff ff ff       	call   1e <mm_malloc+0x1e>
  22:	8b 55 08             	mov    0x8(%ebp),%edx
  25:	8d 5c 1a ff          	lea    -0x1(%edx,%ebx,1),%ebx
  29:	89 5d e0             	mov    %ebx,-0x20(%ebp)
  2c:	89 45 dc             	mov    %eax,-0x24(%ebp)
  2f:	b8 00 10 00 00       	mov    $0x1000,%eax
  34:	29 d0                	sub    %edx,%eax
  36:	89 da                	mov    %ebx,%edx
  38:	81 e2 00 f0 ff ff    	and    $0xfffff000,%edx
  3e:	01 d0                	add    %edx,%eax
  40:	85 c0                	test   %eax,%eax
  42:	0f 8e c0 00 00 00    	jle    108 <mm_malloc+0x108>
  48:	8b 55 08             	mov    0x8(%ebp),%edx
  4b:	83 e8 01             	sub    $0x1,%eax
  4e:	89 f7                	mov    %esi,%edi
  50:	25 00 f0 ff ff       	and    $0xfffff000,%eax
  55:	8d 84 02 00 10 00 00 	lea    0x1000(%edx,%eax,1),%eax
  5c:	89 d3                	mov    %edx,%ebx
  5e:	89 45 e4             	mov    %eax,-0x1c(%ebp)
  61:	eb 51                	jmp    b4 <mm_malloc+0xb4>
  63:	90                   	nop
  64:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
  68:	8b 31                	mov    (%ecx),%esi
  6a:	81 e6 00 f0 ff ff    	and    $0xfffff000,%esi
  70:	81 ee 00 00 00 40    	sub    $0x40000000,%esi
  76:	89 d8                	mov    %ebx,%eax
  78:	c1 e8 0a             	shr    $0xa,%eax
  7b:	25 fc 0f 00 00       	and    $0xffc,%eax
  80:	01 c6                	add    %eax,%esi
  82:	f6 06 01             	testb  $0x1,(%esi)
  85:	75 22                	jne    a9 <mm_malloc+0xa9>
  87:	a1 00 00 00 00       	mov    0x0,%eax
  8c:	3d ff 7f 00 00       	cmp    $0x7fff,%eax
  91:	0f 8f c1 01 00 00    	jg     258 <mm_malloc+0x258>
  97:	89 c1                	mov    %eax,%ecx
  99:	83 c0 01             	add    $0x1,%eax
  9c:	c1 e1 0c             	shl    $0xc,%ecx
  9f:	83 c9 07             	or     $0x7,%ecx
  a2:	89 0e                	mov    %ecx,(%esi)
  a4:	a3 00 00 00 00       	mov    %eax,0x0
  a9:	81 c3 00 10 00 00    	add    $0x1000,%ebx
  af:	3b 5d e4             	cmp    -0x1c(%ebp),%ebx
  b2:	74 54                	je     108 <mm_malloc+0x108>
  b4:	89 d8                	mov    %ebx,%eax
  b6:	c1 e8 16             	shr    $0x16,%eax
  b9:	8d 0c 87             	lea    (%edi,%eax,4),%ecx
  bc:	f6 01 01             	testb  $0x1,(%ecx)
  bf:	75 a7                	jne    68 <mm_malloc+0x68>
  c1:	a1 00 00 00 00       	mov    0x0,%eax
  c6:	89 c6                	mov    %eax,%esi
  c8:	83 c0 01             	add    $0x1,%eax
  cb:	c1 e6 0c             	shl    $0xc,%esi
  ce:	81 c6 00 10 00 00    	add    $0x1000,%esi
  d4:	a3 00 00 00 00       	mov    %eax,0x0
  d9:	8d 86 00 00 00 40    	lea    0x40000000(%esi),%eax
  df:	25 00 f0 ff ff       	and    $0xfffff000,%eax
  e4:	83 c8 07             	or     $0x7,%eax
  e7:	89 01                	mov    %eax,(%ecx)
  e9:	c7 44 24 08 00 10 00 	movl   $0x1000,0x8(%esp)
  f0:	00 
  f1:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
  f8:	00 
  f9:	89 34 24             	mov    %esi,(%esp)
  fc:	e8 fc ff ff ff       	call   fd <mm_malloc+0xfd>
 101:	e9 70 ff ff ff       	jmp    76 <mm_malloc+0x76>
 106:	66 90                	xchg   %ax,%ax
 108:	8b 5d dc             	mov    -0x24(%ebp),%ebx
 10b:	8b 45 e0             	mov    -0x20(%ebp),%eax
 10e:	81 eb 00 00 00 40    	sub    $0x40000000,%ebx
 114:	81 e3 00 f0 ff ff    	and    $0xfffff000,%ebx
 11a:	c1 e8 16             	shr    $0x16,%eax
 11d:	8b 34 83             	mov    (%ebx,%eax,4),%esi
 120:	f7 c6 01 00 00 00    	test   $0x1,%esi
 126:	75 32                	jne    15a <mm_malloc+0x15a>
 128:	c7 44 24 10 24 00 00 	movl   $0x24,0x10(%esp)
 12f:	00 
 130:	c7 44 24 0c 0a 00 00 	movl   $0xa,0xc(%esp)
 137:	00 
 138:	c7 44 24 08 11 00 00 	movl   $0x11,0x8(%esp)
 13f:	00 
 140:	c7 44 24 04 13 00 00 	movl   $0x13,0x4(%esp)
 147:	00 
 148:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 14f:	e8 fc ff ff ff       	call   150 <mm_malloc+0x150>
 154:	b8 01 00 00 00       	mov    $0x1,%eax
 159:	d6                   	(bad)  
 15a:	8b 55 e0             	mov    -0x20(%ebp),%edx
 15d:	8d 86 00 00 00 c0    	lea    -0x40000000(%esi),%eax
 163:	25 00 f0 ff ff       	and    $0xfffff000,%eax
 168:	c1 ea 0c             	shr    $0xc,%edx
 16b:	81 e2 ff 03 00 00    	and    $0x3ff,%edx
 171:	f6 04 90 01          	testb  $0x1,(%eax,%edx,4)
 175:	75 32                	jne    1a9 <mm_malloc+0x1a9>
 177:	c7 44 24 10 2c 00 00 	movl   $0x2c,0x10(%esp)
 17e:	00 
 17f:	c7 44 24 0c 0a 00 00 	movl   $0xa,0xc(%esp)
 186:	00 
 187:	c7 44 24 08 13 00 00 	movl   $0x13,0x8(%esp)
 18e:	00 
 18f:	c7 44 24 04 13 00 00 	movl   $0x13,0x4(%esp)
 196:	00 
 197:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 19e:	e8 fc ff ff ff       	call   19f <mm_malloc+0x19f>
 1a3:	b8 01 00 00 00       	mov    $0x1,%eax
 1a8:	d6                   	(bad)  
 1a9:	8b 45 08             	mov    0x8(%ebp),%eax
 1ac:	c1 e8 16             	shr    $0x16,%eax
 1af:	8b 1c 83             	mov    (%ebx,%eax,4),%ebx
 1b2:	f6 c3 01             	test   $0x1,%bl
 1b5:	75 32                	jne    1e9 <mm_malloc+0x1e9>
 1b7:	c7 44 24 10 24 00 00 	movl   $0x24,0x10(%esp)
 1be:	00 
 1bf:	c7 44 24 0c 0a 00 00 	movl   $0xa,0xc(%esp)
 1c6:	00 
 1c7:	c7 44 24 08 11 00 00 	movl   $0x11,0x8(%esp)
 1ce:	00 
 1cf:	c7 44 24 04 13 00 00 	movl   $0x13,0x4(%esp)
 1d6:	00 
 1d7:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 1de:	e8 fc ff ff ff       	call   1df <mm_malloc+0x1df>
 1e3:	b8 01 00 00 00       	mov    $0x1,%eax
 1e8:	d6                   	(bad)  
 1e9:	8b 55 08             	mov    0x8(%ebp),%edx
 1ec:	8d 83 00 00 00 c0    	lea    -0x40000000(%ebx),%eax
 1f2:	25 00 f0 ff ff       	and    $0xfffff000,%eax
 1f7:	c1 ea 0c             	shr    $0xc,%edx
 1fa:	81 e2 ff 03 00 00    	and    $0x3ff,%edx
 200:	8b 1c 90             	mov    (%eax,%edx,4),%ebx
 203:	f6 c3 01             	test   $0x1,%bl
 206:	75 32                	jne    23a <mm_malloc+0x23a>
 208:	c7 44 24 10 2c 00 00 	movl   $0x2c,0x10(%esp)
 20f:	00 
 210:	c7 44 24 0c 0a 00 00 	movl   $0xa,0xc(%esp)
 217:	00 
 218:	c7 44 24 08 13 00 00 	movl   $0x13,0x8(%esp)
 21f:	00 
 220:	c7 44 24 04 13 00 00 	movl   $0x13,0x4(%esp)
 227:	00 
 228:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 22f:	e8 fc ff ff ff       	call   230 <mm_malloc+0x230>
 234:	b8 01 00 00 00       	mov    $0x1,%eax
 239:	d6                   	(bad)  
 23a:	8b 55 08             	mov    0x8(%ebp),%edx
 23d:	89 d8                	mov    %ebx,%eax
 23f:	25 00 f0 ff ff       	and    $0xfffff000,%eax
 244:	81 e2 ff 0f 00 00    	and    $0xfff,%edx
 24a:	09 d0                	or     %edx,%eax
 24c:	83 c4 3c             	add    $0x3c,%esp
 24f:	5b                   	pop    %ebx
 250:	5e                   	pop    %esi
 251:	5f                   	pop    %edi
 252:	5d                   	pop    %ebp
 253:	c3                   	ret    
 254:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 258:	c7 44 24 10 00 00 00 	movl   $0x0,0x10(%esp)
 25f:	00 
 260:	c7 44 24 0c 00 00 00 	movl   $0x0,0xc(%esp)
 267:	00 
 268:	c7 44 24 08 31 00 00 	movl   $0x31,0x8(%esp)
 26f:	00 
 270:	c7 44 24 04 13 00 00 	movl   $0x13,0x4(%esp)
 277:	00 
 278:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 27f:	e8 fc ff ff ff       	call   280 <mm_malloc+0x280>
 284:	b8 01 00 00 00       	mov    $0x1,%eax
 289:	d6                   	(bad)  
 28a:	a1 00 00 00 00       	mov    0x0,%eax
 28f:	e9 03 fe ff ff       	jmp    97 <mm_malloc+0x97>
